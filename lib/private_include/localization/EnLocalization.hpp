#pragma once

#include "enums/StringId.hpp"
#include "types/StringTypes.hpp"

using enum StringId;

const std::map<StringId, StringView> EN_LOCALIZATION = {
    { PlayButton, "Play" },
    { Options, "Options" },
    { PauseTitle, "Game paused" },
    { ExitButton, "Exit" },
    { Back, "Back" },
    { VideoOptionsTab, "Video" },
    { AudioOptionsTab, "Audio" },
    { EnableFullscreen, "Fullscreen" },
    { SetResolution, "Resolution" },
    { SoundVolume, "Sound volume" },
    { MusicVolume, "Music volume" },
    { Resume, "Resume game" },
    { BackToMenu, "Back to main menu" },
};
