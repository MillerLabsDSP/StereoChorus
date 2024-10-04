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
    
    enum LFOType {
        Sine,
        Square,
        Triangle,
        None
    };
    
    FractionalDelay(InputType inputType, LFOType lfoType) : inputType(inputType), lfoType(lfoType) {};
    ~FractionalDelay() {};
    
    double processSample(double x, int channel);

    void setFs(double Fs);
    void setLFOType(LFOType lfoType);
    void setDelaySamples(double delay);
    void setLFORate(double rate);
    void setLFODepth(double depth);
    void setLFODelay(double delay);
    
private:
    
    void updateAngle(int channel);
    double msToSamples(double ms);

    InputType inputType;
    LFOType lfoType;
    
    LFO lfo;
    
    double Fs = -1.f;
            
    // Delay buffer information
    const int MAX_BUFFER_SIZE = 96000;
    double delayBuffer[96000][2] = {0.f};
    int index[2] = { 0 };
    
    double rate = 1.f;
    double depth = 2.f;
    double offset = 1.f;
    double phase = 0.f;
    
    int delaySamples = 0;
    
    double noiseMix = 0.05f;
    double gamma = 0.f;
    
};
