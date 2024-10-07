/*
  ==============================================================================

    FractionalDelay.cpp
    Created: 4 Jun 2024 2:30:58pm
    Author:  Zachary Miller

  ==============================================================================
*/

#include "FractionalDelay.h"

double FractionalDelay::processSample(double x, int channel) {
    double lfoReturn, delayIn;
    lfoReturn = lfo.calculate(channel);
    delayIn = delaySamples + msToSamples(lfoReturn);
    
    int d1 = std::floor(delayIn);
    int d2 = d1 + 1;
    double g2 = delayIn - (double)d1;
    double g1 = 1.0 - g2;
        
    int indexD1 = index[channel] - d1;
    if (indexD1 < 0) {
        indexD1 += MAX_BUFFER_SIZE;
    }
        
    int indexD2 = index[channel] - d2;
    if (indexD2 < 0) {
        indexD2 += MAX_BUFFER_SIZE;
    }
        
    double y = g1 * delayBuffer[indexD1][channel] + g2 * delayBuffer[indexD2][channel];
        
    delayBuffer[index[channel]][channel] = x;
        
    if (index[channel] < MAX_BUFFER_SIZE - 1){
        index[channel]++;
    }
    else {
        index[channel] = 0;
    }
        
    return y;
}

void FractionalDelay::setFs(double Fs) {
    this->Fs = Fs;
    lfo.setFs(Fs);
}

double FractionalDelay::msToSamples(double ms) {
    return Fs*(ms/1000.0);
}

void FractionalDelay::setDelaySamples(double delay) {
    if (inputType == Milliseconds) {
        double delay_hold = msToSamples(delay);
        if (delay_hold <= MAX_BUFFER_SIZE || delay_hold >= 0.0) {
            delaySamples = delay_hold;
        }
    }
    if (inputType == Samples) {
        if (delay <= MAX_BUFFER_SIZE || delay >= 0.0) {
            this->delaySamples = delay;
        }
    }
}

void FractionalDelay::setLFORate(double rate) {
    this->rate = rate;
    lfo.setRate(rate);
}

void FractionalDelay::setLFODepth(double depth) {
    this->depth = depth;
    lfo.setDepth(depth);
}

void FractionalDelay::setLFOShape(double shape) {
    lfo.setShape(shape);
}
