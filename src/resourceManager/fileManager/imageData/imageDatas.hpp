#pragma once

#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entities/creature/creature.hpp"
#include "game/pageManager/pages/gamePage/gameManager/worldManager/entityManager/entity/entity.hpp"
#include "imageData.hpp"
#include <tuple>
#include <utility>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1st 전방선언
class WorldImageData;
class PlayerImageData;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ImageDatas
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 2nd 여기에 이미지 클래스 추가
    private :
        using ImageClassList = std::tuple<
            WorldImageData,
            PlayerImageData
        >;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 3rd 여기에 이미지 명 추가 (반드시 이미지 파일 순서와 맞게)
    public :
        enum class Name{//이미지 명
            world,
            player,
            COUNT
        };
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

        using IMAGE_DATA = ImageDataInterface;
        using ELEMENT_TYPE = std::unique_ptr<const IMAGE_DATA>;
        using IMAGE_DATAS_TYPE = std::array<ELEMENT_TYPE,tools::CASTs(Name::COUNT)>;
    private :
        IMAGE_DATAS_TYPE image_datas;

        template<typename ImageClass>
        void set_image(sf::Texture&& tex)
        {
            constexpr Name name = ImageClass::name;
            if(image_datas[tools::CASTs(name)])
                throw std::runtime_error("ImageDatas already has image of same name");
            image_datas[tools::CASTs(name)] = std::move(std::make_unique<ImageClass>(std::move(tex)));
        }

        template<size_t... Is>
        void set_all_images(std::vector<sf::Texture>&& textures, std::index_sequence<Is...>)
        {
            (set_image<std::tuple_element_t<Is, ImageClassList>>(
                std::move(textures[tools::CASTs(std::tuple_element_t<Is, ImageClassList>::name)])
             ), ...);
        }
    public :
        ImageDatas() = default;
        ImageDatas(ImageDatas&&) = default;
        ImageDatas& operator=(ImageDatas&&) = default;

        ImageDatas(std::vector<sf::Texture>&& textures)
        {
            static_assert(tools::has_count<Name>(),"ImageDatas::Name has not COUNT");
            if(textures.size() != tools::CASTs(Name::COUNT))
                throw std::runtime_error("Name enum of ImageDatas does not match to textures count");

            set_all_images(
                std::move(textures),
                std::make_index_sequence<std::tuple_size_v<ImageClassList>>{}
            );
        }
        const IMAGE_DATA& operator[](Name image) const {return *image_datas[tools::CASTs(image)];}
        const IMAGE_DATA& operator[](Entity::EntityName name) const
        {
            Name image = Name::world;//임시
            switch(name)
            {
                case Entity::EntityName::player:
                    image = Name::player;
                    break;
                default:
                    throw std::runtime_error("Your EntityName was not mapped to image name");
            }
            return *image_datas[tools::CASTs(image)];
        }

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 4th 이미지클래스 구현
// 1. 이미지 내 crop할 부분이 있다면, 각 subimage 이름에 대한 enum을 추가해야함.
// 2. 각 enum번호에 맞는 SubImageData 추가
// 3. ImageDatas::Name에 자신의 클래스 코드를 static constexpr ImageDatas::Name name으로 추가

class WorldImageData : public ImageData
{
    public :
        static constexpr ImageSize TILE_SIZE = {64,64};
        using CroppedImageName = World::Tile;

        WorldImageData(sf::Texture&& texture)
            : ImageData(std::move(texture),TILE_SIZE)
        {
            add_cropped_image_data(CroppedImageName::GRASS_1, {0,0});
            add_cropped_image_data(CroppedImageName::GRASS_2, {1,0});
            add_cropped_image_data(CroppedImageName::GRASS_3, {2,0});
            add_cropped_image_data(CroppedImageName::CULTIVATE, {0,1});
        }  
        static constexpr ImageDatas::Name name = ImageDatas::Name::world;
};

class PlayerImageData : public ImageData
{
    public :
        static constexpr ImageSize PLAYER_SIZE = {47,128};

        using CroppedImageName = Creature::MovingState;

        PlayerImageData(sf::Texture&& texture)
            : ImageData(std::move(texture),PLAYER_SIZE)
        {
            add_cropped_image_data(CroppedImageName::DOWN_1, {0,0});
            add_cropped_image_data(CroppedImageName::DOWN_2, {1,0});
            add_cropped_image_data(CroppedImageName::DOWN_3, {2,0});
            add_cropped_image_data(CroppedImageName::UP_1, {3,0});
            add_cropped_image_data(CroppedImageName::UP_2, {4,0});
            add_cropped_image_data(CroppedImageName::UP_3, {5,0});
            add_cropped_image_data(CroppedImageName::RIGHT_1, {6,0});
            add_cropped_image_data(CroppedImageName::RIGHT_2, {7,0});
            add_cropped_image_data(CroppedImageName::RIGHT_3, {8,0});
            add_cropped_image_data(CroppedImageName::LEFT_1, {9,0});
            add_cropped_image_data(CroppedImageName::LEFT_2, {10,0});
            add_cropped_image_data(CroppedImageName::LEFT_3, {11,0});
        }  
        const tools::POSi& operator[](Creature::MovingState idx) const
        {
            return cropped_image_datas[tools::CASTs(idx)];
        }

        static constexpr ImageDatas::Name name = ImageDatas::Name::player;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////