#pragma once

#include "gui/Gui.hpp"
#include "input/Input.hpp"
#include "misc/ResourceLoader.hpp"
#include "misc/StringProvider.hpp"
#include <DGM/dgm.hpp>

struct [[nodiscard]] DependencyContainer final
{
    Gui gui;
    dgm::ResourceManager resmgr;
    const StringProvider strings;
    Input input;

    DependencyContainer(
        dgm::Window& window,
        const std::filesystem::path& rootDir,
        Language primaryLang)
        // Gui needs to be instantiated before Resource manager
        // since we need to have gui backend defined before
        // other tgui objects (like fonts) can be created.
        : gui(window)
        , resmgr(ResourceLoader::loadResources(rootDir))
        , strings(primaryLang)
    {
    }
};
