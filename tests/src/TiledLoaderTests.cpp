#include "Helper.hpp"
#include "Paths.hpp"
#include <catch_amalgamated.hpp>
#include <loaders/TiledLoader.hpp>
#include <nlohmann/json.hpp>

TEST_CASE("[TiledLoader]")
{
    SECTION("Can load demo file")
    {
        tiled::FiniteMapModel model =
            TiledLoader::loadLevel(TESTFILES_PATH / "tiled-map-01.json");

        REQUIRE(model.width == 64u);
        REQUIRE(model.height == 64u);
        REQUIRE(model.tilewidth == 64u);
        REQUIRE(model.tileheight == 64u);

        REQUIRE(model.layers.size() == 1u);
    }
}