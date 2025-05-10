#include "misc/ResourceLoader.hpp"
#include "misc/Compatibility.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Tgui.hpp>
#include <expected>

static std::expected<tgui::Font, dgm::Error>
loadTguiFont(const std::filesystem::path& path)
{
    return tgui::Font(path.string());
}

dgm::ResourceManager
ResourceLoader::loadResources(const std::filesystem::path& rootDir)
{
    dgm::ResourceManager resmgr;

    if (auto result = resmgr.loadResourcesFromDirectory<sf::Font>(
            rootDir / "assets" / "fonts", dgm::Utility::loadFont, { ".ttf" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load font: {}", result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<tgui::Font>(
            rootDir / "assets" / "fonts", loadTguiFont, { ".ttf" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load font: {}", result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<sf::Texture>(
            rootDir / "assets" / "graphics",
            dgm::Utility::loadTexture,
            { ".png" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load texture: {}", result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<dgm::AnimationStates>(
            rootDir / "assets" / "graphics",
            dgm::Utility::loadAnimationStates,
            { ".anim" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load animation states: {}",
            result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<dgm::Clip>(
            rootDir / "assets" / "graphics",
            dgm::Utility::loadClip,
            { ".clip" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load clip: {}", result.error().getMessage()));
    }

    if (auto result = resmgr.loadResourcesFromDirectory<sf::SoundBuffer>(
            rootDir / "assets" / "sounds", dgm::Utility::loadSound, { ".wav" });
        !result)
    {
        throw std::runtime_error(uni::format(
            "Could not load sound: {}", result.error().getMessage()));
    }

    return resmgr;
}
