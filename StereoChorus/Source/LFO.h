/*
  ==============================================================================

    LFO.h
    Created: 4 Jun 2024 1:27:45pm
    Author:  Zachary Miller

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <cmath>
#include <string>

class LFO {
public:

    LFO() {};
    ~LFO() {};
    
    float calculate(const int channel); // calculate periodic LFO values

    void setFs(double Fs);
    void setRate(double rate);
    void setDepth(double depth);
    void setDelay(double delay);
    void setShape(double shape);
    void setPhase(double phase);

private:
    
    void updateClock(); // sample and hold only
                    
    double Fs = -1.0;
    double Ts = 1/Fs;
                 
    /* VAR INITIALIZERS */
    double angleChange, lfoValue, lfoValue_sin, lfoValue_tri;
    double sine, triangle;
    double currentAngle[2] = { 0.0 };

    double rate, depth, shape, phase = M_PI;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFO)
};
