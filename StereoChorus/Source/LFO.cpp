/*
  ==============================================================================

    LFO.cpp
    Created: 4 Jun 2024 1:27:45pm
    Author:  Zachary Miller

  ==============================================================================
*/

#include "LFO.h"

float LFO::calculate(double rate, double depth, double delay, double phase, const int channel) {
            
    switch (signalType) {
            
        case Sine:
            
            angleChange = rate * Ts * M_PI_X2;
            
            lfoValue = depth * std::sin(currentAngle.at(channel) + phase) + delay;
            
            currentAngle.at(channel) += angleChange;
            
            if (currentAngle.at(channel) > M_PI_X2) {
                currentAngle.at(channel) = 0.0;
            }
            
            return lfoValue;
            break;
            
        case Cosine:
            
            angleChange = rate * Ts * M_PI_X2;
            
            lfoValue = depth * std::cos(currentAngle.at(channel)) + delay;
            
            currentAngle.at(channel) += angleChange;
            
            if (currentAngle.at(channel) > M_PI_X2) {
                currentAngle.at(channel) = 0.0;
            }
            
            return lfoValue;
            
        case Square:
            
            angleChange = rate * Ts * M_PI_X2;
            
            square = std::sin(currentAngle.at(channel)) >= 0.0 ? -1.0:1.0;
            lfoValue = depth * square + delay;
            
            currentAngle.at(channel) += angleChange;
            
            if (currentAngle.at(channel) > M_PI_X2) {
                currentAngle.at(channel) = 0.0;
            }
            
            return lfoValue;
            
        case Triangle:
            
            angleChange = rate * Ts * M_PI_X2;
            
            triangle = -std::acos(std::sin(currentAngle.at(channel)))/(M_PI_2) + 1;
            lfoValue = depth * triangle + delay;
            
            currentAngle.at(channel) += angleChange;
            
            if (currentAngle.at(channel) > M_PI_X2) {
                currentAngle.at(channel) = 0.0;
            }
            
            return lfoValue;
            
        case SineToTriangle:
            
            angleChange = rate * Ts * M_PI_X2;
            
            // SINE
            lfoValue_sin = depth * std::sin(currentAngle.at(channel)) + delay;
            
            // TRIANGLE
            triangle = -std::acos(std::sin(currentAngle.at(channel)))/(M_PI_2) + 1;
            lfoValue_tri = depth * triangle + delay;
            
            currentAngle.at(channel) += angleChange;
            
            if (currentAngle.at(channel) > M_PI_X2) {
                currentAngle.at(channel) = 0.;
            }
            
            return (1.0 - mix) * lfoValue_sin + mix * lfoValue_tri;
                        
    }
}

void LFO::setFs(double Fs) {
    this->Fs = Fs;
    this->Ts = 1.0/Fs;
}

void LFO::setLFOType(LFO::SignalType signalType) {
    this->signalType = signalType;
}

void LFO::setRate(double rate) {
    this->rate = rate;
}

void LFO::setDepth(double depth) {
    this->depth = depth;
}

void LFO::setDelay(double delay) {
    this->delay = delay;
}
