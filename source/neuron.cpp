//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Neuron.h"

Neuron::Neuron() : membraneV(V_RESET), threshold(THRESHOLD), tau(TAU), res(RESISTANCE) {
    membranePotentials.push_back(getPotential());
}

void Neuron::update(double time, Current* inC) {

    if (refractory) {
        // potential reset as spike has been hit in iteration before
        setPotential(V_RESET);

    } else if (getPotential() > getThreshold()) {
        // spike recorded
        spikeTimes.push_back(time);
        // neuron now in refractory mode
        setRefractory(true);
        // refractory time set so neuron can "do it's time"
        reftime = REFRACTORY_TIME;

    } else {
        setPotential(
                exp(-(TIME_H/tau)) * getPotential() + inC->getValue() * res * (1 - exp(-(TIME_H/tau)))
        ); // solving membrane equation to evolve potential over time

        // if above threshold, potential set to 0 in order to set spike
        if(getPotential() > getThreshold()) {
            setPotential(0);
        }
    }

    // potential stored over time
    membranePotentials.push_back(getPotential()); // stores membrane potential in vector

}

void Neuron::updateState() {
    if(refractory) {
        if(reftime <= 0) {
            // neuron has "done it's time"
            refractory = false;
            if(reftime == 0){
                // reset potential when sentence is done
                setPotential(V_RESET);
            }
        } else {
            // evolves time left
            reftime -= TIME_H;
        }
    }
}

// getters
bool Neuron::getRefractory() const {
    return refractory;
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
void Neuron::setRefractory(bool s) {
    refractory = s;
}

void Neuron::setPotential(double v) {
    membraneV = v;
}