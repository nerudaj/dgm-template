#pragma once

#include <misc/DependencyContainer.hpp>
#include <misc/ResourceLoader.hpp>

struct [[nodiscard]] TestContext final
{
    dgm::Window window;
    DependencyContainer dic;
};

class Helper final
{
public:
    dgm::Window createDummyWindow()
    {
        return dgm::Window(dgm::WindowSettings {
            .resolution = {1u, 1u},
            .title = "",
            .useFullscrren = false,
        });
    }

    DependencyContainer createDummyDependencies(dgm::Window& window)
    {
        return DependencyContainer
        {
            .resmgr = ResourceLoader::loadResources(),
            .strings = StringProvider(Language::English),
            .gui = Gui(window),
            .input = Input(),
        };
    }
};
