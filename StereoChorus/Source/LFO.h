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
    
    enum SignalType {
        Sine,
        Cosine,
        Square,
        Triangle,
        SineToTriangle,
    };

    LFO() {};
    LFO(SignalType signalType) : signalType(signalType) {};
    ~LFO() {};
    
    float calculate(double rate, double depth, double delay, double phase, const int channel); // calculate periodic LFO values

    void setFs(double Fs);
    void setRate(double rate);
    void setDepth(double depth);
    void setDelay(double delay);
    void setLFOType(SignalType signalType);

private:
    
    void updateClock(); // sample and hold only
    
    SignalType signalType;
                
    double Fs = -1.0;
    double Ts = 1.0/Fs;
    
    double M_PI_X2 = M_PI * 2.0;
             
    /* VAR INITIALIZERS */
    double angleChange, lfoValue, lfoValue_sin, lfoValue_tri;
    double square, triangle;
    std::array<double,2> currentAngle = { 0.f };

    double rate, delay, depth, mix;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFO)

};
