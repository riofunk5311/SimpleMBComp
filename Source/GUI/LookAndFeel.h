/*
  ==============================================================================

    LookAndFeel.h
    Created: 3 Feb 2022 7:28:06pm
    Author:  Ryota Sugawara

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct LookAndFeel : juce::LookAndFeel_V4
{
    void drawRotarySlider(juce::Graphics&,
                          int x, int y, int width, int height,
                          float sliderPosProportional,
                          float rotaryStartAngle,
                          float rotaryEndAngle,
                          juce::Slider&) override;
    
    void drawToggleButton(juce::Graphics &g,
                          juce::ToggleButton & toggleButton,
                          bool shouldDrawButtonAsHighlighted,
                          bool shouldDrawButtonAsDown) override;
};

