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
    EnableFullscreen,
    SetResolution,
    SoundVolume,
    MusicVolume,
    Resume,
    BackToMenu,
    MaxId, // Make sure this one is always the last!
};
