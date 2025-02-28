#pragma once

#include "misc/DependencyContainer.hpp"
#include "settings/InputSettings.hpp"
#include <DGM/dgm.hpp>

class CommonHandler final
{
public:
    static void handleInput(
        dgm::App& app, DependencyContainer& dic, const InputSettings& settings);
};
