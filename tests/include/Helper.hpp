#pragma once

#include "Paths.hpp"
#include <misc/DependencyContainer.hpp>
#include <misc/ResourceLoader.hpp>

class Helper final
{
public:
    static dgm::Window createDummyWindow()
    {
        return dgm::Window(dgm::WindowSettings {
            .resolution = { 1u, 1u },
            .title = "",
            .useFullscreen = false,
        });
    }

    static DependencyContainer createDummyDependencies(dgm::Window& window)
    {
        return DependencyContainer(window, ASSETS_PATH, Language::English);
    }
};

class GuiHelper
{
public:
    static void clickButton(tgui::Button::Ptr button)
    {
        button->leftMousePressed(
            button->getPosition() + button->getSize() / 2.f);
        button->leftMouseReleased(
            button->getPosition() + button->getSize() / 2.f);
    }
};