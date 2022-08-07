#pragma once

namespace ImGuiGradient {

using Flags = int;

namespace Flag {
// TODO(ASG) Documentation on each flag
enum ImGuiGradientFlag {
    None                 = 0,
    NoTooltip            = 1 << 1,
    NoResetButton        = 1 << 2,
    NoLabel              = 1 << 3,
    NoRandomModeChange   = 1 << 4, // TODO(ASG) Probably rename this, I don't understand what it does if I have only the name
    NoAddButton          = 1 << 5,
    NoRemoveButton       = 1 << 6,
    NoPositionSlider     = 1 << 7,
    NoColorEdit          = 1 << 8,
    NoWrapModeCombo      = 1 << 9,  // TODO(ASG) rename combo as selector
    NoInterpolationCombo = 1 << 10, // TODO(ASG) same
    NoDragDowntoDelete   = 1 << 11, // TODO(ASG) missing an upper case for "to"
    NoBorder             = 1 << 12,
    NoAddAndRemoveButton = NoAddButton | NoRemoveButton, // TODO(ASG) missing a "s" at the end
    NoMarkOptions        = NoColorEdit | NoPositionSlider,
    NoCombo              = NoInterpolationCombo | NoWrapModeCombo, // TODO(ASG) rename combo as selector
};

} // namespace Flag
} // namespace ImGuiGradient
