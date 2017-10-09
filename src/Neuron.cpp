//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Neuron.h"


Neuron::Neuron() : membraneV(V_RESET) {
    membranePotentials.push_back(getPotential());
}

void Neuron::update(double time, const Current& inC) {

    // first, we wish to know if the neuron is already in a refractory state or not
    if(getRefractory()) {
        // if this is the case, we set the potential to V_RESET
        setPotential(V_RESET);
        // if there is remaining refractory time, we decrease it by one timestep
        if(getRefTime() >= 0) {
            setRefTime(getRefTime() - 1);
        } else {
            // otherwise, we change the state to inactive (non refractory)
            setRefractory(false);
        }
    } else {
        // the neuron is not in a refractory state, we must affect it's potential using the diff equation
        setPotential(
                exp(-(TIME_H/TAU)) * getPotential() + RESISTANCE * (1 - exp(-(TIME_H/TAU))) * inC.getValue(time * TIME_H)
        );

        // we must now test if this value is above the neuron's threshold
        if(getPotential() > V_THRESHOLD) {
            // the potential will spike once it is above the threshold
            setPotential(V_RESET);
            // the spike is recorded in our records in the specified vector
            spikeTimes.push_back(time);
            // we must now set the neuron in refractory mode
            setRefractory(true);
            // finally, the refractory time is set in order to let the neuron "do it's time"
            setRefTime(REFRACTORY_TIME);
        }
        // in the case that the new potential is below the threshold, we simply continue the simulation
    }

    // in any case, the neuron's potential will be stored over time
    membranePotentials.push_back(getPotential());

    // and finally, we will update the neuron's local clock
    ++clock;
}

// Getters
bool Neuron::getRefractory() const {
    return refractory;
}

double Neuron::getPotential() const {
    return membraneV;
}

double Neuron::getRefTime() const {
    return reftime;
}

int Neuron::getSpikesNumber() const {
    return (int)spikeTimes.size();
}

std::vector<double> Neuron::getMembraneV() const {
    return membranePotentials;
}

// Setters
void Neuron::setRefractory(bool s) {
    refractory = s;
}

void Neuron::setPotential(double v) {
    membraneV = v;
}

void Neuron::setRefTime(double r) {
    reftime = r;
}