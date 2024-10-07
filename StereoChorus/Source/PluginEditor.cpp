/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
StereoChorusAudioProcessorEditor::StereoChorusAudioProcessorEditor (StereoChorusAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p) 
{
    setSize(400, 300);
}

StereoChorusAudioProcessorEditor::~StereoChorusAudioProcessorEditor() 
{
}

//==============================================================================
void StereoChorusAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void StereoChorusAudioProcessorEditor::resized()
{
}
