#pragma once

#include "misc/DependencyContainer.hpp"
#include "settings/AppSettings.hpp"
#include <DGM/dgm.hpp>

class [[nodiscard]] AppStateOptions final : public dgm::AppState
{
public:
    AppStateOptions(
        dgm::App& app,
        DependencyContainer& dic,
        AppSettings& settings) noexcept;

public:
    void input() override;
    void update() override;
    void draw() override;

private:
    void buildLayout();

    void buildVideoOptionsLayout();

    void buildAudioOptionsLayout();

    void onTabClicked(const tgui::String& tabName);

    void onBack();

    void onResolutionSelected(const sf::Vector2u& resolution);

private:
    DependencyContainer& dic;
    AppSettings& settings;
    tgui::Panel::Ptr content;
};
