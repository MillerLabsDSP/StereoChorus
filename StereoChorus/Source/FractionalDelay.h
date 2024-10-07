/*
  ==============================================================================

    FractionalDelay.h
    Created: 4 Jun 2024 2:30:58pm
    Author:  Zachary Miller

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <cmath>
#include "LFO.h"

class FractionalDelay {
public:
    
    enum InputType {
        Samples,
        Milliseconds
    };
        
    FractionalDelay() {};
    ~FractionalDelay() {};
    
    double processSample(double x, int channel);

    void setFs(double Fs);
    void setDelaySamples(double delay);
    void setLFORate(double rate);
    void setLFODepth(double depth);
    void setLFOShape(double shape);
    
private:
    
    void updateAngle(int channel);
    double msToSamples(double ms);

    LFO lfo;
    
    InputType inputType;
    
    double Fs = -1.f;
            
    constexpr static int MAX_BUFFER_SIZE = 96000;
    constexpr static int MAX_NUM_CHANNELS = 2;
    double delayBuffer[MAX_BUFFER_SIZE][MAX_NUM_CHANNELS] = { 0.0 };
    int index[MAX_NUM_CHANNELS] = { 0 };
    
    double rate, depth, delay, phase;
    int delaySamples = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FractionalDelay)
};
