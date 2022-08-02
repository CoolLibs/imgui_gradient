#pragma once

typedef int GradientOptions; // TODO(ASG) put flag in the name (if ImGui does that, TODO check it)
// TODO(ASG) Make the flags part of the options ?

enum GradientOptions_ {
    GradientOptions_None                   = 0,
    GradientOptions_NoTooltip              = 1 << 1,
    GradientOptions_NoResetButton          = 1 << 2,
    GradientOptions_NoLabel                = 1 << 3,
    GradientOptions_NoRandomModeChange     = 1 << 4,
    GradientOptions_NoAddButton            = 1 << 5,
    GradientOptions_NoRemoveButton         = 1 << 6,
    GradientOptions_NoPositionSlider       = 1 << 7,
    GradientOptions_NoColorEdit            = 1 << 8,
    GradientOptions_NoPositionModeCombo    = 1 << 9,
    GradientOptions_NoInterpolationCombo   = 1 << 10,
    GradientOptions_NoDragDowntoDelete     = 1 << 11,
    GradientOptions_NoBorder               = 1 << 12,
    GradientOptions_NoAddAndRemoveButton   = GradientOptions_NoAddButton | GradientOptions_NoRemoveButton,
    GradientOptions_NoMarkOptions          = GradientOptions_NoColorEdit | GradientOptions_NoPositionSlider,
    GradientOptions_NoCombo                = GradientOptions_NoInterpolationCombo | GradientOptions_NoPositionModeCombo,
    GradientOptions_NoComboAndRandomMode   = GradientOptions_NoRandomModeChange | GradientOptions_NoCombo,
    GradientOptions_NoButtonAndMarkOptions = GradientOptions_NoAddAndRemoveButton | GradientOptions_NoMarkOptions,
};