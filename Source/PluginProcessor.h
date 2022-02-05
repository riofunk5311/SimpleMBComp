/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

/*
 GUI RoadMap:
 1) Global Controls (x-over sliders, gain sliders) Done
 2) Main Band Controls (attack, release, threshold, ratio) Done
 3) add solo/mute/bypass buttons Done
 4) Banc Select Functionality Done
 5) Banc Select Buttons reflect the Solo/Mute/Bypass state Done
 6) Custom Look and Feel for Sliders and Toggle Buttons Done
 7) Spectrum Analyzer Overview Done
 8) Data Structre for Spectrum Analyzer Done
 9) Fifo usage in pluginProcessor::processBlock
 10) implementation of the analyzer rendering pre-computed paths
 11) Drawing crossovers on top of the Analyzer Plot
 12) Drawing gain reduction on top of the analyzer
 13 Analyzer Bypass
 14) Global Bypass Button
 */

#include <JuceHeader.h>
#include "DSP/CompressorBand.h"
#include "DSP/SingleChannelSampleFifo.h"

//==============================================================================
/**
*/
class SimpleMBCompAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SimpleMBCompAudioProcessor();
    ~SimpleMBCompAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    using APVTS = juce::AudioProcessorValueTreeState;
    static APVTS::ParameterLayout createParameterLayout();
        
    APVTS apvts {*this, nullptr, "Parameters", createParameterLayout() };
    
    using BlockType = juce::AudioBuffer<float>;
       SingleChannelSampleFifo<BlockType> leftChannelFifo { Channel::Left };
       SingleChannelSampleFifo<BlockType> rightChannelFifo { Channel::Right };
private:
    std::array<CompressorBand, 3> compressors;
    CompressorBand& lowBandComp = compressors[0];
    CompressorBand& midBandComp = compressors[1];
    CompressorBand& highBandComp = compressors[2];
    
    using Filter = juce::dsp::LinkwitzRileyFilter<float>;
    //     fc0  fc1
    Filter LP1, AP2,
           HP1, LP2,
                HP2;
    
//    Filter invAP1, invAP2;
//    juce::AudioBuffer<float> invAPBuffer; 
    
    juce::AudioParameterFloat* lowMidCrossover {nullptr};
    juce::AudioParameterFloat* midHighCrossover {nullptr};
    
    std::array<juce::AudioBuffer<float>, 3 > filterBuffers;
    
    juce::dsp::Gain<float> inputGain, outputGain;
    juce::AudioParameterFloat* inputGainParam {nullptr};
    juce::AudioParameterFloat* outputGainParam {nullptr};
    
    template<typename T, typename U>
    void applyGain(T& buffer, U& gain)
    {
        auto block = juce::dsp::AudioBlock<float>(buffer);
        auto ctx = juce::dsp::ProcessContextReplacing<float>(block);
        gain.process(ctx);
    }
    
    void updateState();
    
    void splitBands(const juce::AudioBuffer<float>& inputBuffer);
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleMBCompAudioProcessor)
};
