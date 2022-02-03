/*
  ==============================================================================

    UtilityComponents.cpp
    Created: 3 Feb 2022 7:42:51pm
    Author:  Ryota Sugawara

  ==============================================================================
*/

#include "UtilityComponents.h"

Placeholder::Placeholder()
{
    juce::Random r;
    customColor = juce::Colour(r.nextInt(255), r.nextInt(255), r.nextInt(255));
}

void Placeholder::paint(juce::Graphics& g)
{
    g.fillAll(customColor);
}
//==============================================================================
RotarySlider::RotarySlider() :
juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
             juce::Slider::TextEntryBoxPosition::NoTextBox)
{}
