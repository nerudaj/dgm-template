#include "appstate/AppStateOptions.hpp"
#include "appstate/CommonHandler.hpp"
#include "gui/Builders.hpp"
#include "misc/Compatibility.hpp"
#include <ranges>

const tgui::Color CONTENT_BGCOLOR = tgui::Color(255, 255, 255, 64);

std::string resolutionToString(const sf::Vector2u& vec)
{
    return uni::format("{}x{}", vec.x, vec.y);
}

static std::vector<std::string> getResolutionStrings()
{
    return sf::VideoMode::getFullscreenModes()
           | std::views::transform([](const sf::VideoMode& mode)
                                   { return mode.size; })
           | std::views::transform(resolutionToString)
           | uniranges::to<std::vector>();
}

static std::string intValueFormatter(float val)
{
    return std::to_string(static_cast<int>(val));
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
                            dic.strings.getString(StringId::InputOptionsTab),
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
                    [&](size_t idx)
                    {
                        onResolutionSelected(
                            sf::VideoMode::getFullscreenModes()[idx].size);
                    }))
            .build(CONTENT_BGCOLOR));
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
                    SliderProperties { .valueFormatter = intValueFormatter,
                                       .low = 0.f,
                                       .high = 100.f,
                                       .step = 1.f }))
            .addOption(
                dic.strings.getString(StringId::SoundVolume),
                WidgetBuilder::createSlider(
                    settings.audio.soundVolume,
                    [&](float val) { settings.audio.soundVolume = val; },
                    dic.gui,
                    SliderProperties { .valueFormatter = intValueFormatter,
                                       .low = 0.f,
                                       .high = 100.f,
                                       .step = 1.f }))
            .build(CONTENT_BGCOLOR));
}

void AppStateOptions::buildInputOptionsLayout()
{
    content->removeAllWidgets();
    content->add(
        FormBuilder()
            .addOption(
                dic.strings.getString(StringId::GamepadDeadzone),
                WidgetBuilder::createSlider(
                    settings.input.gamepadDeadzone,
                    [&](float val) { settings.input.gamepadDeadzone = val; },
                    dic.gui,
                    SliderProperties { .valueFormatter = intValueFormatter,
                                       .low = 0.f,
                                       .high = 100.f,
                                       .step = 1.f }))
            .addOption(
                dic.strings.getString(StringId::CursorSpeed),
                WidgetBuilder::createSlider(
                    settings.input.cursorSpeed,
                    [&](float val) { settings.input.cursorSpeed = val; },
                    dic.gui,
                    SliderProperties { .valueFormatter = intValueFormatter,
                                       .low = 100.f,
                                       .high = 1000.f,
                                       .step = 10.f }))
            .build(CONTENT_BGCOLOR));
}

void AppStateOptions::onTabClicked(const tgui::String& tabName)
{
    if (tabName == dic.strings.getString(StringId::VideoOptionsTab))
        buildVideoOptionsLayout();
    else if (tabName == dic.strings.getString(StringId::AudioOptionsTab))
        buildAudioOptionsLayout();
    else if (tabName == dic.strings.getString(StringId::InputOptionsTab))
        buildInputOptionsLayout();
}

void AppStateOptions::onBack()
{
    app.popState();
}

void AppStateOptions::onResolutionSelected(const sf::Vector2u& resolution)
{
    settings.video.resolution = resolution;
    app.window.changeResolution(resolution);
    dic.gui.setWindow(app.window.getSfmlWindowContext());

    // must be recreated, otherwise it disappears for some reason
    content = WidgetBuilder::createPanel();

    buildLayout();

    // TODO: Open "Are you sure dialog?"
}
