#pragma once

namespace ImGuiGradient {

using Flags = int;

namespace Flag {

enum ImGuiGradientFlag {
    None                    = 0,                                            // All Options are enabled
    NoTooltip               = 1 << 1,                                       // No tooltip when hovering a widget
    NoResetButton           = 1 << 2,                                       // No button to reset to the default value
    NoLabel                 = 1 << 3,                                       // No name for gradient widget
    NoRandomModeCheckBox    = 1 << 4,                                       // No checkbox to enable or disable the random mode when adding a new color
    NoAddButton             = 1 << 5,                                       // No "+" button to add a mark
    NoRemoveButton          = 1 << 6,                                       // No "-" button to remove a mark
    NoPositionSlider        = 1 << 7,                                       // No slider widget to chose a precise position when selecting a mark
    NoColorEdit             = 1 << 8,                                       // No color edit widget when selecting a mark
    NoWrapModeSelector      = 1 << 9,                                       // No widget to change wrap mode position
    NoInterpolationSelector = 1 << 10,                                      // No widget to change how gradient colors are computed
    NoDragDownToDelete      = 1 << 11,                                      // Don't delete a mark by dragging it down
    NoBorder                = 1 << 12,                                      // No border around gradient widget
    NoAddAndRemoveButtons   = NoAddButton | NoRemoveButton,                 // No "+" and "-" buttons
    NoMarkOptions           = NoColorEdit | NoPositionSlider,               // No new widgets appear when a brand is selected
    NoSelector              = NoInterpolationSelector | NoWrapModeSelector, // No selector to change wrap mode position and  how gradient colors are computed
};

} // namespace Flag
} // namespace ImGuiGradient
