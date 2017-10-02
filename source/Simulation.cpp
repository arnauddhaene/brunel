//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"

Simulation::Simulation() : time(0) {
    // Neuron and Current pointer creation
    neuron = new Neuron();
    inCurrent = new Current;
}

void Simulation::TimeIncrement() {
    // Time incrementation
    time += TIME_H;
}

void Simulation::loop(double timeA, double timeB) {
    // Neuron update
    neuron->update(getSimulationTime(), inCurrent);

    // Increments time
    TimeIncrement();
}

void Simulation::run(double timeA, double timeB) {

    while(time >= timeA and time <= timeB) {
        loop(timeA, timeB);
    }

}

double Simulation::getSimulationTime() const {
    return time;
}

std::vector<double> Simulation::getNeuronV() const {
    return neuron->getMembraneV();
}