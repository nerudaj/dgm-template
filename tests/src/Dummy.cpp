#include <appstate/AppStateMainMenu.hpp>
#include <appstate/AppStatePause.hpp>
#include <catch_amalgamated.hpp>

TEST_CASE("[Dummy]")
{
    dgm::Window window({ 1u, 1u }, "", false);
    dgm::App app(window);
    app.pushState<AppStateMainMenu>();
    app.pushState<AppStatePause>();
}
