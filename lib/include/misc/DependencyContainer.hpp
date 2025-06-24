#pragma once

#include "filesystem/ResourceLoader.hpp"
#include "gui/Gui.hpp"
#include "input/Input.hpp"
#include "input/VirtualCursor.hpp"
#include "settings/AppSettings.hpp"
#include "strings/StringProvider.hpp"
#include <DGM/dgm.hpp>

struct [[nodiscard]] DependencyContainer final
{
    Gui gui;
    dgm::ResourceManager resmgr;
    const StringProvider strings;
    Input input;
    VirtualCursor virtualCursor;

    DependencyContainer(
        dgm::Window& window,
        const std::filesystem::path& rootDir,
        Language primaryLang,
        const AppSettings& settings)
        // Gui needs to be instantiated before Resource manager
        // since we need to have gui backend defined before
        // other tgui objects (like fonts) can be created.
        : gui(window)
        , resmgr(ResourceLoader::loadResources(rootDir))
        , strings(primaryLang)
        , input(settings.bindings)
        , virtualCursor(
              window.getSfmlWindowContext(),
              input,
              resmgr.get<sf::Texture>("cursor.png"))
    {
        gui.setFont(resmgr.get<tgui::Font>("ChunkFive-Regular.ttf"));
        // NOTE: You can create your own theme file and use it here
        // gui.setTheme(resmgr.get<tgui::Theme::Ptr>("TransparentGrey.txt"));
    }
};
