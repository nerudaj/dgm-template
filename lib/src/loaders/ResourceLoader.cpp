#include "loaders/ResourceLoader.hpp"
#include "loaders/TiledLoader.hpp"
#include "misc/AppStorage.hpp"
#include "misc/Compatibility.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Tgui.hpp>
#include <expected>

static std::expected<tgui::Font, dgm::Error>
loadTguiFont(const std::filesystem::path& path)
{
    return tgui::Font(path.string());
}

static std::expected<tiled::FiniteMapModel, dgm::Error>
loadTiledMap(const std::filesystem::path& path)
{
    try
    {
        return TiledLoader::loadLevel(path);
    }
    catch (const std::exception& ex)
    {
        return std::unexpected { dgm::Error(ex.what()) };
    }
}

dgm::ResourceManager
ResourceLoader::loadResources(const std::filesystem::path& assetDir)
{
    dgm::ResourceManager resmgr;

    if (auto result = resmgr.loadResourcesFromDirectory<sf::Font>(
            assetDir / "fonts", dgm::Utility::loadFont, { ".ttf" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load font: {}", result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<tgui::Font>(
            assetDir / "fonts", loadTguiFont, { ".ttf" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load font: {}", result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<sf::Texture>(
            assetDir / "graphics", dgm::Utility::loadTexture, { ".png" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load texture: {}", result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<dgm::AnimationStates>(
            assetDir / "graphics",
            dgm::Utility::loadAnimationStates,
            { ".anim" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load animation states: {}",
            result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<dgm::Clip>(
            assetDir / "graphics", dgm::Utility::loadClip, { ".clip" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load clip: {}", result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<sf::SoundBuffer>(
            assetDir / "sounds", dgm::Utility::loadSound, { ".wav" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load sound: {}", result.error().getMessage()));
    }

    return resmgr;
}

AppSettings ResourceLoader::loadSettings(const std::filesystem::path& file)
{
    auto settingsJson = InternalStorage::loadFile(file);

    if (settingsJson)
    {
        try
        {
            AppSettings settings = nlohmann::json::parse(settingsJson.value());
            return settings;
        }
        catch (const std::exception& ex)
        {
            sf::err() << ex.what() << std::endl;
        }
    }

    return AppSettings {
        .video =
            VideoSettings {
#ifdef ANDROID
                .resolution = sf::VideoMode::getDesktopMode().size,
#elif _DEBUG
                .resolution = { 1280, 720 },
#else
                .resolution = sf::VideoMode::getDesktopMode().size,
#endif
            },
    };
}
