/*
  ==============================================================================

    UtilityComponents.h
    Created: 3 Feb 2022 7:42:51pm
    Author:  Ryota Sugawara

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct Placeholder : juce::Component
{
    Placeholder();
    
    void paint(juce::Graphics& g) override;
   
    juce::Colour customColor;
};

struct RotarySlider : juce::Slider
{
    RotarySlider();
};
