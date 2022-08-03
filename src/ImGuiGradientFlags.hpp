#pragma once

typedef int ImGuiGradientFlags;
// TODO(ASG) Make the flags part of the options ?

enum ImGuiGradientFlags_ {
    ImGuiGradientFlags_None                 = 0,
    ImGuiGradientFlags_NoTooltip            = 1 << 1,
    ImGuiGradientFlags_NoResetButton        = 1 << 2,
    ImGuiGradientFlags_NoLabel              = 1 << 3,
    ImGuiGradientFlags_NoRandomModeChange   = 1 << 4,
    ImGuiGradientFlags_NoAddButton          = 1 << 5,
    ImGuiGradientFlags_NoRemoveButton       = 1 << 6,
    ImGuiGradientFlags_NoPositionSlider     = 1 << 7,
    ImGuiGradientFlags_NoColorEdit          = 1 << 8,
    ImGuiGradientFlags_NoPositionModeCombo  = 1 << 9,
    ImGuiGradientFlags_NoInterpolationCombo = 1 << 10,
    ImGuiGradientFlags_NoDragDowntoDelete   = 1 << 11,
    ImGuiGradientFlags_NoBorder             = 1 << 12,
    ImGuiGradientFlags_NoAddAndRemoveButton = ImGuiGradientFlags_NoAddButton | ImGuiGradientFlags_NoRemoveButton,
    ImGuiGradientFlags_NoMarkOptions        = ImGuiGradientFlags_NoColorEdit | ImGuiGradientFlags_NoPositionSlider,
    ImGuiGradientFlags_NoCombo              = ImGuiGradientFlags_NoInterpolationCombo | ImGuiGradientFlags_NoPositionModeCombo,
};