/*
  ==============================================================================

    CustomButtons.h
    Created: 3 Feb 2022 7:38:08pm
    Author:  Ryota Sugawara

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct PowerButton : juce::ToggleButton {};

struct AnalyzerButton : juce::ToggleButton
{
    void resized() override;
    
    juce::Path randomPath;
};
