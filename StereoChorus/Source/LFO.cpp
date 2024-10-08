/*
  ==============================================================================

    LFO.cpp
    Created: 4 Jun 2024 1:27:45pm
    Author:  Zachary Miller

  ==============================================================================
*/

#include "LFO.h"

float LFO::calculate(const int channel) {
    angleChange = rate * Ts * 2 * M_PI;
    
    double phaseIn = (channel == 0) ? 0 : phase;
    sine = depth * std::sin(currentAngle[channel] + phaseIn);
    triangle = depth * (-std::acos(std::sin(currentAngle[channel] + phaseIn)) / M_PI_2 + 1);
    
    currentAngle[channel] += angleChange;
    if (currentAngle[channel] > 2 * M_PI) {
        currentAngle[channel] = 0.0;
    }
    
    return (1 - shape) * sine + shape * triangle;
}

void LFO::setFs(double Fs) {
    this->Fs = Fs;
    this->Ts = 1.0/Fs;
}

void LFO::setRate(double rate) {
    this->rate = rate;
}

void LFO::setDepth(double depth) {
    this->depth = depth;
}

void LFO::setShape(double shape) {
    this->shape = shape;
}

void LFO::setPhase(double phase) {
    this->phase = phase;
}
