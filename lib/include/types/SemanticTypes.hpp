#pragma once

#include "types/BrandedType.hpp"
#include <SFML/System/Vector2.hpp>

using Direction = BrandedType<sf::Vector2f, struct DirectionTypeTag>;
using Position = BrandedType<sf::Vector2f, struct PositionTypeTag>;
