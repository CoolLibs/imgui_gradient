#pragma once

using ImGuiGradientFlags = int;

namespace ImGuiGradient { namespace Flags {

enum ImGuiGradientFlags_ {
    None                 = 0,
    NoTooltip            = 1 << 1,
    NoResetButton        = 1 << 2,
    NoLabel              = 1 << 3,
    NoRandomModeChange   = 1 << 4,
    NoAddButton          = 1 << 5,
    NoRemoveButton       = 1 << 6,
    NoPositionSlider     = 1 << 7,
    NoColorEdit          = 1 << 8,
    NoWrapModeCombo      = 1 << 9,
    NoInterpolationCombo = 1 << 10,
    NoDragDowntoDelete   = 1 << 11,
    NoBorder             = 1 << 12,
    NoAddAndRemoveButton = NoAddButton | NoRemoveButton,
    NoMarkOptions        = NoColorEdit | NoPositionSlider,
    NoCombo              = NoInterpolationCombo | NoWrapModeCombo,
};

}} // namespace ImGuiGradient::Flags
