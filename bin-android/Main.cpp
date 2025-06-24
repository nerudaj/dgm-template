#include <appstate/AppStateMainMenu.hpp>
#include <DGM/dgm.hpp>
#include <filesystem/AppStorage.hpp>
#include <misc/CMakeVars.hpp>
#include <misc/Compatibility.hpp>
#include <misc/DependencyContainer.hpp>
#include <SFML/System/Err.hpp>

const auto SETTINGS_FILE_NAME = std::filesystem::path("settings.json");

int main(int, char*[])
{
    try
    {
        auto&& settings = ResourceLoader::loadSettings(SETTINGS_FILE_NAME);

        auto&& window = dgm::Window(dgm::WindowSettings {
            .resolution = settings.video.resolution,
            .title = CMakeVars::TITLE,
            .useFullscreen = settings.video.fullscreen,
        });
        auto&& app = dgm::App(window);
        auto&& dependencies = DependencyContainer(window, "", Language::English, settings);

        window.getSfmlWindowContext().setMouseCursorVisible(false);

        app.pushState<AppStateMainMenu>(dependencies, settings);
        app.run();
        
        AppStorage::saveFile(
            SETTINGS_FILE_NAME, nlohmann::json(settings).dump(4));
    }
    catch (const std::exception& ex)
    {
        sf::err() << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
