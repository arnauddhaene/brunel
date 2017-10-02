//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"

Simulation::Simulation() : time(0) {
    neuron = new Neuron();
    inCurrent = new Current;
}

void Simulation::TimeIncrement() {
    time += TIME_H;
}

void Simulation::loop(double timeA, double timeB) {

    neuron->update(getSimulationTime(), inCurrent);

    neuron->updateState();

    TimeIncrement(); // increments time
}

void Simulation::run(double timeA, double timeB) {

    while(time >= timeA and time <= timeB) {
        loop(timeA, timeB);
    }

}

// getters
double Simulation::getSimulationTime() const {
    return time;
}

std::vector<double> Simulation::getNeuronV() const {
    return neuron->getMembraneV();
}