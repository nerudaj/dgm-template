#pragma once

#include "gui/Gui.hpp"
#include "input/Input.hpp"
#include "misc/StringProvider.hpp"
#include <DGM/dgm.hpp>

struct [[nodiscard]] DependencyContainer final
{
    dgm::ResourceManager resmgr;
    const StringProvider strings;
    Gui gui;
    Input input;
};
