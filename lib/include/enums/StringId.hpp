#pragma once

// localizations can be found under private_include/localizations

enum class [[nodiscard]] StringId
{
    PlayButton,
    Options,
    PauseTitle,
    ExitButton,
    Back,
    VideoOptionsTab,
    AudioOptionsTab,
    InputOptionsTab,
    EnableFullscreen,
    SetResolution,
    SoundVolume,
    MusicVolume,
    GamepadDeadzone,
    CursorSpeed,
    Resume,
    BackToMenu,
    MaxId, // Make sure this one is always the last!
};
