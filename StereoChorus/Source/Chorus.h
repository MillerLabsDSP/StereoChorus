/*
  ==============================================================================

    Chorus.h
    Created: 3 Jun 2024 1:54:42pm
    Author:  Zachary Miller

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <string>
#include "FractionalDelay.h"
#include "LFO.h"

class Chorus {
public:
    
    Chorus() {};
    ~Chorus() {};
    
    void prepareToPlay(const double Fs, const int bufferSize);
    double processSample(double input, const int channel);
    void processBuffer(juce::AudioBuffer<float>& buffer);
    
    /* Fractional delay setters */
    void setFracRate(double rate);
    void setFracDepth(double depth);
    void setFracDelay(double delay);
    
private:
        
    FractionalDelay fd { FractionalDelay::InputType::Milliseconds, FractionalDelay::LFOType::Sine };
    
    double Fs = -1.0;
    int bufferSize = -1;
    
    // Input hold buffer
    double output = 0, input[2] = { 0.0 };
    
    /* VAR INITIALIZERS */
    double rate, depth, delay, mix;
    
    constexpr static int left = 0, right = 1;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chorus)

};
