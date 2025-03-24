#include <DGM/dgm.hpp>
#include <appstate/AppStateMainMenu.hpp>
#include <misc/CMakeVars.hpp>
#include <misc/DependencyContainer.hpp>
#include <misc/Compatibility.hpp>
#include <mutex>

std::expected<tgui::Font, dgm::Error>
loadTguiFont(const std::filesystem::path& path)
{
    return tgui::Font(path.string());
}

dgm::ResourceManager
initializeResourceManager(const std::filesystem::path& rootDir)
{
    dgm::ResourceManager resmgr;

    if (auto result = resmgr.loadResourcesFromDirectory<sf::Font>(
            rootDir  / "fonts", dgm::Utility::loadFont, { ".ttf" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load font: {}", result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<tgui::Font>(
            rootDir  / "fonts", loadTguiFont, { ".ttf" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load font: {}", result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<sf::Texture>(
            rootDir  / "graphics",
            dgm::Utility::loadTexture,
            { ".png" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load texture: {}", result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<dgm::AnimationStates>(
            rootDir  / "graphics",
            dgm::Utility::loadAnimationStates,
            { ".anim" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load animation states: {}",
            result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<dgm::Clip>(
            rootDir  / "graphics",
            dgm::Utility::loadClip,
            { ".clip" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load clip: {}", result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<sf::SoundBuffer>(
            rootDir  / "sounds", dgm::Utility::loadSound, { ".wav" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load sound: {}", result.error().getMessage()));
    }

    return resmgr;
}

int main(int, char*[])
{
    // TODO: Resolve appdata folder
    // TODO: Attept to load settings from appdata

    auto&& settings = AppSettings {
        .video =
            VideoSettings {
#ifdef _DEBUG
                .resolution = sf::VideoMode::getDesktopMode().size,
#else
                .resolution = sf::VideoMode::getDesktopMode().size,
#endif
            },
    };

    auto&& window = dgm::Window(dgm::WindowSettings {
        .resolution = settings.video.resolution,
        .title = CMakeVars::TITLE,
        .useFullscreen = settings.video.fullscreen,
    });
    auto&& app = dgm::App(window);

    tgui::Gui gui(window.getSfmlWindowContext());
    tgui::Theme guiTheme;

    try
    {
        auto dependencies = DependencyContainer {
            .resmgr = initializeResourceManager(""),
            .strings = StringProvider(Language::English),
            .gui = Gui(gui, guiTheme),
            .input = Input(),
        };

        gui.setFont(
            dependencies.resmgr.get<tgui::Font>("ChunkFive-Regular.ttf"));

        app.pushState<AppStateMainMenu>(dependencies, settings);
        app.run();
    }
    catch (const std::exception& ex)
    {
        sf::err() << ex.what() << std::endl;
        return 1;
    }

    // TODO: capture window settings
    // TODO: store settings in appdata

    return 0;
}
