//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"
#include <cmath>


Simulation::Simulation() {}

void Simulation::TimeIncrement() const {
    time += time_h;
}

void Simulation::NeuronLoop() {

    if (neuron.getState() == refractory) {
        neuron.setPotential(0);
    } else if (neuron.getPotential() > neuron.getThreshold()) {
        neuron.spikeTimes.push_back(getSimulationTime());
    }

    neuron.setPotential(
            exp(-(time_h/tau)) * neuron.getPotential() + inCurrent * res * (1 - exp(-(time_h/tau)))
    ); // solving membrane equation

    TimeIncrement(); // increments time
}

// getters
double Simulation::getSimulationTime() const {
    return time;
}