#pragma once

#include "tools/hasWHAT.hpp"
#include "tools/pos.hpp"
#include "tools/cast.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <typeindex>

class ImageSize
{
    private :
        tools::POSs size;
    public :
        constexpr ImageSize() = default;
        constexpr ImageSize(const tools::POSs& size)
            : size(size)
        {
            if(size.x < 0 || size.y < 0)
                throw std::runtime_error("CroppedImageSize size is less than 0");
        }
        constexpr ImageSize(tools::POSs&& size)
            : size(std::move(size))
        {
            if(size.x < 0 || size.y < 0)
                throw std::runtime_error("CroppedImageSize size is less than 0");
        }
        constexpr ImageSize(int x, int y)
            : size(x, y)
        {
            if(x <= 0 || y <= 0)
                throw std::runtime_error("CroppedImageSize size is less than 0");
        }
        constexpr tools::POSs get(float scale = 1.0) const
        {
            if(scale <= 0)
                throw std::runtime_error("CroppedImageSize scale is less than 0");
            return size*scale;
        }
};


class ImageDataInterface
{
    private :
        const sf::Texture texture;
        const ImageSize cropped_size;
        std::vector<tools::POSi> cropped_image_datas;

        std::type_index enum_type;
        bool has_enum_type;
    protected :
        template<typename T>
        void add_cropped_image_data(T cropped_image_name, tools::POSi&& cropped_image_pos)
        {
            if(std::is_void<T>::value)
                throw std::runtime_error("there is no CroppedImageName in the image, but tried to add its data");
            static_assert(std::is_enum<T>::value, "CroppedImageName is not enum");
            static_assert(tools::has_count<T>(), "CroppedImageName has not COUNT");
            
            if(!has_enum_type)
            {
                enum_type = std::type_index(typeid(T));
                has_enum_type = true;
            }
            else if(std::type_index(typeid(T)) != enum_type)
                throw std::runtime_error("Mismatched CroppedImageName type used for add_cropped_image_data!");
            
            if(cropped_image_datas.size() != tools::CASTs(T::COUNT))
                cropped_image_datas.resize(tools::CASTs(T::COUNT));
            cropped_image_datas[tools::CASTs(cropped_image_name)] = std::move(cropped_image_pos*cropped_size.get());
        }
    public :
        ImageDataInterface(sf::Texture&& texture, const ImageSize& cropped_size)
            : texture(std::move(texture))
            , cropped_size(cropped_size)
            , enum_type(typeid(void))
            , has_enum_type(false)
        {}
        virtual ~ImageDataInterface() = default;

        sf::Sprite get_sprite() const
        {
            return sf::Sprite(texture);
        }

        tools::POSi size(float scale = 1.0) const {return cropped_size.get(scale);}

        template<typename T>
        const tools::POSi& operator[](T idx) const
        {
            if(std::is_void<T>::value)
                throw std::runtime_error("there is no CroppedImageName in the image, but tried to get it");

            if (has_enum_type && std::type_index(typeid(T)) != enum_type)
                throw std::runtime_error("Mismatched CroppedImageName type used for operator[]!");

            return cropped_image_datas[tools::CASTs(idx)];
        }
};

class ImageData : public ImageDataInterface
{
    public:
        ImageData(sf::Texture&& tex, const ImageSize& cropped_size)
            : ImageDataInterface(std::move(tex), cropped_size)
        {}
};
