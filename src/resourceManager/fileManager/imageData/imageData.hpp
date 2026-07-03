#pragma once

#include "tools/hasWHAT.hpp"
#include "tools/pos.hpp"
#include "tools/cast.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <typeindex>

class CroppedImageSize
{
    private :
        tools::POSi __size;
    public :
        CroppedImageSize() = default;
        CroppedImageSize(const tools::POSi& size)
            : __size(size)
        {}
        CroppedImageSize(tools::POSi&& size)
            : __size(std::move(size))
        {}
        CroppedImageSize(int x, int y)
            : __size(x, y)
        {}
        tools::POSi size(float scale) const {return __size*scale;}
};

class CroppedImageData
{
    private :
        tools::POSi __pos;
        CroppedImageSize __size;
    public :
        CroppedImageData() = default;
        CroppedImageData(tools::POSi&& pos, CroppedImageSize&& size)
            : __pos(std::move(pos))
            , __size(std::move(size))
        {};
        CroppedImageData(const tools::POSi& pos, const CroppedImageSize& size)
            : __pos(pos)
            , __size(size)
        {};
        CroppedImageData& operator=(const CroppedImageData& sub_image_data)
        {
            __pos = sub_image_data.__pos;
            __size = sub_image_data.__size;
            return *this;
        }
        tools::POSi pos() const {return __pos;}
        tools::POSi size(float scale) const {return __size.size(scale);}
};


class ImageDataInterface
{
    private :
        const sf::Texture texture;
        std::vector<CroppedImageData> cropped_image_datas;
        std::type_index enum_type;
        bool has_enum_type;
    protected :
        template<typename T>
        void add_cropped_image_data(T cropped_image_name, CroppedImageData&& sub_image_data)
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
            cropped_image_datas[tools::CASTs(cropped_image_name)] = std::move(sub_image_data);
        }
    public :
        ImageDataInterface(sf::Texture&& texture)
            : texture(std::move(texture))
            , enum_type(typeid(void))
            , has_enum_type(false)
        {}
        virtual ~ImageDataInterface() = default;

        sf::Sprite get_sprite() const
        {
            return sf::Sprite(texture);
        }

        template<typename T>
        const CroppedImageData& operator[](T idx) const
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
        ImageData(sf::Texture&& tex)
            : ImageDataInterface(std::move(tex))
        {}
};
