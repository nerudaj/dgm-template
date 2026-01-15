#include "Helper.hpp"
#include <catch_amalgamated.hpp>

TEST_CASE("[Sanity]")
{
    SECTION("Can create dummy window and dependencies")
    {
        auto window = Helper::createDummyWindow();
        auto dic = Helper::createDummyDependencies(window);
        REQUIRE(true);
    }

    SECTION("Can default-create settings and serialize-deserialize them")
    {
        const std::string& json = nlohmann::json(AppSettingsStorageModel {}).dump(4);
        const AppSettingsStorageModel settings = nlohmann::json::parse(json);
    }
}
