//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Neuron.h"


Neuron::Neuron(unsigned int id) : membraneV(V_RESET), refractory(false), ID(id), buffer(0) {
    membranePotentials.push_back(getPotential());

    // connections.push_back(1);
}

void Neuron::update(double time, const Current& inC, Neuron& conneur) {

    // first, we wish to know if the neuron is already in a refractory state or not
    if(getRefractory()) {
        // if this is the case, we set the potential to V_RESET
        setPotential(V_RESET);
        // if there is remaining refractory time, we decrease it by one timestep
        if(getRefTime() > 0) {
            setRefTime(getRefTime() - 1);
        } else {
            // otherwise, we change the state to inactive (non refractory)
            setRefractory(false);
            setRefTime(0);
        }
    } else {
        // the neuron is not in a refractory state, we must affect it's potential using the diff equation
        setPotential(
                (exp(-(TIME_H/TAU)) * getPotential() + RESISTANCE * (1 - exp(-(TIME_H/TAU))) * inC.getValue(time * TIME_H)) + buffer
        );

        // now we must reset the buffer
        if(buffer != 0) buffer = 0;

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

            // we now wish to send spike to connecting neuron : neuron2
            if(&conneur != nullptr) {
                conneur.recieveSpike(15.0);
            }
        }
        // in the case that the new potential is below the threshold, we simply continue the simulation
    }

    // in any case, the neuron's potential will be stored over time
    membranePotentials.push_back(getPotential());

    // we will update the neuron's local clock
    ++clock;
}

void Neuron::recieveSpike(double amplitude) {
    buffer = amplitude;
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