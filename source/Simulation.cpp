//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"

Simulation::Simulation() : time(0) {
    // creation of new simulation with pointers on neuron and current
    neuron = new Neuron();
    inCurrent = new Current;
}

void Simulation::TimeIncrement() {
    // time incrementation by value from constants file
    time += TIME_H;
}

void Simulation::loop(double timeA, double timeB) {

    neuron->update(getSimulationTime(), inCurrent);

    // useful for refractory state issues
    neuron->updateState();

    TimeIncrement(); // increments time
}

void Simulation::run(double timeA, double timeB) {

    // runs the simulation between t(start) and t(stop)
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