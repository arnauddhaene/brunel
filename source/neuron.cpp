//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Neuron.h"

void Neuron::update(double time) {

    if (getState() == refractory) {
        setPotential(0);
    } else if (getPotential() > getThreshold()) {
        spikeTimes.push_back(time);
    }

    setPotential(
            exp(-(time_h/tau)) * neuron.getPotential() + inCurrent * res * (1 - exp(-(time_h/tau)))
    ); // solving membrane equation

}

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