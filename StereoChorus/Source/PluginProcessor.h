/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Chorus.h"

//==============================================================================
/**
*/
class StereoChorusAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    StereoChorusAudioProcessor();
    ~StereoChorusAudioProcessor() override;

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

private:
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::AudioProcessorValueTreeState apvts { *this, nullptr, "Parameters", createParameterLayout() };
        
    Chorus chorus;
//    LFO lfo; // debug only
//    FractionalDelay fd;
    
    constexpr static int NUM_PARAMS = 6;
    std::vector<float> param_values = { 0.f };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoChorusAudioProcessor)
};
