#include "appstate/AppStateOptions.hpp"
#include "appstate/CommonHandler.hpp"
#include "gui/Builders.hpp"
#include <ranges>

std::string resolutionToString(const sf::Vector2u& vec)
{
    return std::format("{}x{}", vec.x, vec.y);
}

static std::vector<std::string> getResolutionStrings()
{
    return sf::VideoMode::getFullscreenModes()
           | std::views::transform([](const sf::VideoMode& mode)
                                   { return mode.size; })
           | std::views::transform(resolutionToString)
           | std::ranges::to<std::vector>();
}

AppStateOptions::AppStateOptions(
    dgm::App& app, DependencyContainer& dic, AppSettings& settings) noexcept
    : dgm::AppState(app)
    , dic(dic)
    , settings(settings)
    , content(WidgetBuilder::createPanel())
{
    buildLayout();
}

void AppStateOptions::input()
{
    CommonHandler::handleInput(app, dic, settings.input);
}

void AppStateOptions::update() {}

void AppStateOptions::draw()
{
    dic.gui.draw();
}

void AppStateOptions::buildLayout()
{
    dic.gui.rebuildWith(
        DefaultLayoutBuilder()
            .withNoBackgroundImage()
            .withTitle(
                dic.strings.getString(StringId::Options), HeadingLevel::H1)
            .withContent(
                NavbarLayoutBuilder()
                    .withNavbarWidget(WidgetBuilder::createTabbedContent(
                        {
                            dic.strings.getString(StringId::VideoOptionsTab),
                            dic.strings.getString(StringId::AudioOptionsTab),
                        },
                        [&](const tgui::String& tabName)
                        { onTabClicked(tabName); }))
                    .withContent(content)
                    .build())
            .withBackButton(WidgetBuilder::createButton(
                dic.strings.getString(StringId::Back), [&] { onBack(); }))
            .withNoSubmitButton()
            .build());

    // TODO: configure controls

    buildVideoOptionsLayout();
}

void AppStateOptions::buildVideoOptionsLayout()
{
    content->removeAllWidgets();
    content->add(
        FormBuilder()
            .addOption(
                dic.strings.getString(StringId::EnableFullscreen),
                WidgetBuilder::createCheckbox(
                    settings.video.fullscreen,
                    [&](bool val)
                    {
                        settings.video.fullscreen = val;
                        app.window.toggleFullscreen();
                    }))
            .addOption(
                dic.strings.getString(StringId::SetResolution),
                WidgetBuilder::createDropdown(
                    getResolutionStrings(),
                    resolutionToString(settings.video.resolution),
                    [&](size_t idx) {
                        onResolutionSelected(
                            sf::VideoMode::getFullscreenModes()[idx].size);
                    }))
            .build(tgui::Color(255, 255, 255, 64)));
}

void AppStateOptions::buildAudioOptionsLayout()
{
    content->removeAllWidgets();
    content->add(
        FormBuilder()
            .addOption(
                dic.strings.getString(StringId::MusicVolume),
                WidgetBuilder::createSlider(
                    settings.audio.musicVolume,
                    [&](float val) { settings.audio.musicVolume = val; },
                    dic.gui,
                    WidgetBuilder::SliderProperties {
                        .low = 0.f, .high = 100.f, .step = 1.f }))
            .addOption(
                dic.strings.getString(StringId::SoundVolume),
                WidgetBuilder::createSlider(
                    settings.audio.soundVolume,
                    [&](float val) { settings.audio.soundVolume = val; },
                    dic.gui,
                    WidgetBuilder::SliderProperties {
                        .low = 0.f, .high = 100.f, .step = 1.f }))
            .build(tgui::Color(255, 255, 255, 64)));
}

void AppStateOptions::onTabClicked(const tgui::String& tabName)
{
    if (tabName == dic.strings.getString(StringId::VideoOptionsTab))
        buildVideoOptionsLayout();
    else if (tabName == dic.strings.getString(StringId::AudioOptionsTab))
        buildAudioOptionsLayout();
}

void AppStateOptions::onBack()
{
    app.popState();
}

void AppStateOptions::onResolutionSelected(const sf::Vector2u& resolution)
{
    settings.video.resolution = resolution;
    app.window.changeResolution(resolution);
    dic.gui.setWindow(app.window.getWindowContext());
    buildLayout();

    // TODO: Open "Are you sure dialog?"
}
