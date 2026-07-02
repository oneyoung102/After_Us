#pragma once

#include "tools/pos.hpp"
#include <SFML/Graphics.hpp>
#include <array>

namespace image_constant//화면을 구성하는 이미지 크기와 관련한 상수
{
    constexpr auto TILE_SIZE = tools::POSi(64,64);
    //worldAsset
    enum TileCode
    {
        VOID = -1,
        GRASS_1,GRASS_2,GRASS_3,
        CULTIVATE,
        COUNT
    };
    constexpr std::array<tools::POSi,TileCode::COUNT> TILE_POS = {
        tools::POSi(0, 0), 
        tools::POSi(1, 0), 
        tools::POSi(2, 0), 
        tools::POSi(0, 1)
    };
    //Text
        constexpr int TEXT_ZOOM_SIZE_PROP = 30, TEXT_ZOOM_CYCLE_PROP = 15;
    //button
        constexpr int TEXT_SIZE_IN_BUTTON = 31;//5글자 기준 기본 텍스트 사이즈
    constexpr float BRIGHTNESS = 0.15;
    constexpr int PRINT_IMMORTAL = -1;
};