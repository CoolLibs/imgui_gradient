#pragma once

namespace ImGuiGradient {

using Flags = int;

namespace Flag {
// TODO(ASG) Documentation on each flag
enum ImGuiGradientFlag {
    None                    = 0,
    NoTooltip               = 1 << 1,
    NoResetButton           = 1 << 2,
    NoLabel                 = 1 << 3,
    NoRandomModeCheckBox    = 1 << 4,
    NoAddButton             = 1 << 5,
    NoRemoveButton          = 1 << 6,
    NoPositionSlider        = 1 << 7,
    NoColorEdit             = 1 << 8,
    NoWrapModeSelector      = 1 << 9,
    NoInterpolationSelector = 1 << 10,
    NoDragDownToDelete      = 1 << 11,
    NoBorder                = 1 << 12,
    NoAddAndRemoveButtons   = NoAddButton | NoRemoveButton,
    NoMarkOptions           = NoColorEdit | NoPositionSlider,
    NoSelector              = NoInterpolationSelector | NoWrapModeSelector,
};

} // namespace Flag
} // namespace ImGuiGradient
