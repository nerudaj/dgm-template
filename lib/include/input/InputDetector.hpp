#pragma once

#include "types/Binding.hpp"
#include <functional>

class [[nodiscard]] InputDetector final
{
public:
    using ReportKmbCallbackType = std::function<void(KmbBinding)>;
    using ReportGamepadCallbackType = std::function<void(GamepadBinding)>;
    using CancelCallbackType = std::function<void()>;
    using ReadyForInputsCallbackType = std::function<void()>;

public:
    InputDetector(ReadyForInputsCallbackType markReadyForInputs)
        : markReadyForInputs(markReadyForInputs)
    {
    }

public:
    using ReportKmbCallbackType = std::function<void(KmbBinding)>;
    using ReportGamepadCallbackType = std::function<void(GamepadBinding)>;
    using CancelCallbackType = std::function<void()>;
    using ReadyForInputsCallbackType = std::function<void()>;

    void startCheckingInputs(
        ReportKmbCallbackType reportCallback, CancelCallbackType cancelCallback)
    {
        reportKmb = reportCallback;
        cancel = cancelCallback;
        runMode = RunMode::DetectingKmb;
        isWaitingForInputsToClear = true;
    }

    void startCheckingInputs(
        ReportGamepadCallbackType reportCallback,
        CancelCallbackType cancelCallback)
    {
        reportGamepad = reportCallback;
        cancel = cancelCallback;
        runMode = RunMode::DetectingGamepad;
        isWaitingForInputsToClear = true;
    }

    void update();

    NODISCARD_RESULT bool isDetectionInProgress() const noexcept
    {
        return runMode != RunMode::Idle;
    }

private:
    enum class [[nodiscard]] RunMode
    {
        Idle,
        DetectingKmb,
        DetectingGamepad,
    };

    enum class [[nodiscard]] DetectionStatus
    {
        None,
        InputDetected
    };

    DetectionStatus tryGamepadAxis();

    DetectionStatus tryGamepadButton();

    DetectionStatus tryKeyboard();

    DetectionStatus tryMouse();

    NODISCARD_RESULT bool isAnyInputPressed() const;

private:
    RunMode runMode = RunMode::Idle;
    ReadyForInputsCallbackType markReadyForInputs;
    ReportKmbCallbackType reportKmb;
    ReportGamepadCallbackType reportGamepad;
    CancelCallbackType cancel;
    bool isWaitingForInputsToClear = true;
};
