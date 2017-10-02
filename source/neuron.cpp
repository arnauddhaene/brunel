//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Neuron.h"

Neuron::Neuron() : membraneV(V_RESET), threshold(THRESHOLD), tau(TAU), res(RESISTANCE) {
    membranePotentials.push_back(getPotential());
}

void Neuron::update(double time, Current* inC) {

    if (getState() == refractory) {
        setPotential(V_RESET);
    } else if (getPotential() > getThreshold()) {
        spikeTimes.push_back(time);
        setState(refractory);
        reftime = REFRACTORY_TIME;
    } else {
        setPotential(
                exp(-(TIME_H/tau)) * getPotential() + inC->getValue() * res * (1 - exp(-(TIME_H/tau)))
        ); // solving membrane equation

        if(getPotential() > getThreshold()) {
            setPotential(0);
        }
    }



    membranePotentials.push_back(getPotential()); // stores membrane potential in vector

}

void Neuron::updateState() {
    if(nState == refractory) {
        if(reftime <= 0) {
            nState = inactive;
            if(reftime == 0){
                setPotential(V_RESET);
            }
        } else {
            reftime -= TIME_H;
        }
    }
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

std::vector<double> Neuron::getMembraneV() const {
    return membranePotentials;
}

// setters
void Neuron::setState(State s) {
    nState = s;
}

void Neuron::setPotential(double v) {
    membraneV = v;
}