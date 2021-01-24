#pragma once

#include "Color.h"

namespace Pallete
{
    struct Planet
    {
        vec4d deepSea, sea, beach, soil, mountain;
    };
    static const Planet BLUE_PLANET = {
        Color::MEDIUM_PERSIAN_BLUE,
        Color::CORNFLOWER_BLUE,
        Color::WHITE,
        Color::GREEN_YELLOW,
        Color::DARK_GOLDENROD};
    static const Planet CINNAMON_PLANET = {
        {0.3, 0.29, 0.27, 1.0},   // dark grey
        {0.7, 0.7, 0.62, 1.0},    // greyish
        {0.9, 0.85, 0.75, 1.0},   // light grey
        {0.78, 0.46, 0.125, 1.0}, // light brown
        {0.26, 0.12, 0.06, 1.0},  // dark brown
    };
} // namespace Pallete
