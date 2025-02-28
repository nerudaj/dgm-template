#pragma once

struct [[nodiscard]] InputSettings final
{
    float cursorSpeed = 500.f; // TODO: migrate to pxpersecond
    float gamepadDeadzone = 10.f;
};
