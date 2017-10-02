//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Neuron.h"

// getters
State Neuron::getState() const {
    return nState;
}

double Neuron::getPotential() const {
    return membraneV;
}

double Neuron::getThreshold() const {
    return threshold;
}

int Neuron::getSpikesNumber() const {
    return (int)spikeTimes.size();
}

// setters
void Neuron::setState(State s) {
    nState = s;
}

void Neuron::setPotential(double v) {
    membraneV = v;
}