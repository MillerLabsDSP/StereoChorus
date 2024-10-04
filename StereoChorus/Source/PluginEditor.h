/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class StereoChorusAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                            public juce::Slider::Listener
{
public:
    StereoChorusAudioProcessorEditor (StereoChorusAudioProcessor&);
    ~StereoChorusAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged (juce::Slider * slider) override;

private:

    StereoChorusAudioProcessor& audioProcessor;
    
    juce::Slider pot1; // Rate
    juce::Slider pot2; // Depth
    juce::Slider pot3; // Delay
    juce::Slider pot4; // Width

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoChorusAudioProcessorEditor)
};
