#pragma once

#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>

struct [[nodiscard]] VideoSettings final
{
    sf::Vector2u resolution = { 1280, 720 };
    bool fullscreen = false;
};

namespace sf
{
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector2u, x, y);
}

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(VideoSettings, resolution, fullscreen);
