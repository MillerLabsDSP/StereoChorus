/*
  ==============================================================================

    Chorus.cpp
    Created: 3 Jun 2024 1:54:42pm
    Author:  Zachary Miller

  ==============================================================================
*/

#include "Chorus.h"

Chorus::Chorus(juce::AudioProcessorValueTreeState vts) {
    apvts = &vts;
}

void Chorus::prepareToPlay(double sampleRate, int bufferSize) {
    this->Fs = sampleRate;
    this->bufferSize = bufferSize;
    fd.setFs(Fs);
}

void Chorus::setFracRate(double rate) {
    this->rate = rate;
    fd.setLFORate(rate);
}

void Chorus::setFracDepth(double depth) {
    this->depth = depth;
    fd.setLFODepth(depth);
}

void Chorus::setFracDelay(double delay) {
    this->delay = delay;
    fd.setDelaySamples(delay);
}

void Chorus::setFracShape(double shape) {
    fd.setLFOShape(shape);
}

void Chorus::setMix(double mix) {
    this->mix = mix;
}

void Chorus::setPhase(double phase) {
    fd.setLFOPhase(phase);
}

double Chorus::processSample(double input, const int channel) {
    output = fd.processSample(input, channel);
    return (1-mix) * input + mix * output;
}

void Chorus::processBuffer(juce::AudioBuffer<float>& buffer) {
    
    auto* channelData_left = buffer.getWritePointer(left);
    auto* channelData_right = buffer.getWritePointer(right);
    
    for (int i = 0; i < bufferSize; ++i) {
        
        input[left] = channelData_left[i];
        input[right] = channelData_right[i];
        
        channelData_left[i] = processSample(input[left], left);
        channelData_right[i] = processSample(input[right], right);
        
    }

}
