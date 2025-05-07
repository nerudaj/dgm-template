#include <appstate/AppStateMainMenu.hpp>
#include <appstate/AppStatePause.hpp>
#include <catch_amalgamated.hpp>
#include <Helper.hpp>

TEST_CASE("[Dummy]")
{
    auto window = Helper::createDummyWindow();
    auto dic = Helper::createDummyDependencies(window);

    REQUIRE(true);
}
