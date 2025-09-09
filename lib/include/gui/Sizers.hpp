#pragma once

#include "settings/VideoSettings.hpp"

class [[nodiscard]] Sizers final
{
public:
    constexpr explicit Sizers(const VideoSettings& settings) noexcept
        : settings(settings)
    {
    }

    Sizers(Sizers&&) = default;
    Sizers(const Sizers&) = delete;

public:
    [[nodiscard]] unsigned getBaseFontSize() const;

    [[nodiscard]] unsigned getBaseContainerHeight() const;

private:
    const VideoSettings& settings;
};
