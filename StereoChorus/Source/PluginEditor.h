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
class StereoChorusAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    StereoChorusAudioProcessorEditor (StereoChorusAudioProcessor&);
    ~StereoChorusAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    StereoChorusAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoChorusAudioProcessorEditor)
};
