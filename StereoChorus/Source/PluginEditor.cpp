/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
StereoChorusAudioProcessorEditor::StereoChorusAudioProcessorEditor (StereoChorusAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p) {

    setSize(525, 150);
    
    // Rate (Hz) test knob
    pot1.addListener(this);
    pot1.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    pot1.setBounds(25, 30, 100, 100);
    pot1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    pot1.setRange(0.5,15.0,0.001);
    pot1.setValue(1.0);
    addAndMakeVisible(pot1);
    
    // Depth test knob
    pot2.addListener(this);
    pot2.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    pot2.setBounds(150, 30, 100, 100);
    pot2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    pot2.setRange(0.0,2.0,0.001);
    pot2.setValue(1.0);
    addAndMakeVisible(pot2);
    
    // Delay (ms) test knob
    pot3.addListener(this);
    pot3.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    pot3.setBounds(275, 30, 100, 100);
    pot3.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    pot3.setRange(0.0,2.0,0.001);
    pot3.setValue(1.0);
    addAndMakeVisible(pot3);
    
    // Stereo test knob
    pot4.addListener(this);
    pot4.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    pot4.setBounds(400, 30, 100, 100);
    pot4.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    pot4.setRange(0.0,1.0,0.001);
    pot4.setValue(1.0);
    addAndMakeVisible(pot4);
    
}

StereoChorusAudioProcessorEditor::~StereoChorusAudioProcessorEditor() {

}

//==============================================================================
void StereoChorusAudioProcessorEditor::paint (juce::Graphics& g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText("Rate", 25, 15, 100, 25, juce::Justification::centred, 1);
    g.drawFittedText("Depth", 150, 15, 100, 25, juce::Justification::centred, 1);
    g.drawFittedText("Delay", 275, 15, 100, 25, juce::Justification::centred, 1);
    g.drawFittedText("Stereo", 400, 15, 100, 25, juce::Justification::centred, 1);}

void StereoChorusAudioProcessorEditor::resized() {

}

void StereoChorusAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    
    if (slider == &pot1){
        audioProcessor.pot1 = slider->getValue();
    }
    if (slider == &pot2){
        audioProcessor.pot2 = slider->getValue();
    }
    if (slider == &pot3){
        audioProcessor.pot3 = slider->getValue();
    }
    if (slider == &pot4){
        audioProcessor.pot4 = slider->getValue();
    }
}
