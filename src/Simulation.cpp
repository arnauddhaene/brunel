//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"

Simulation::Simulation() : time(0) {
    // Neuron and Current pointer creation
    neuron = new Neuron;

    inCurrent = new Current;
}

void Simulation::TimeIncrement() {
    // Time incrementation
    ++time;
}

void Simulation::loop() {
    // Neuron update
    neuron->update(getSimulationTime(), *inCurrent);

    // Increments time
    TimeIncrement();
}

void Simulation::run(double timeA, double timeB) {

    assert(timeA >= 0);
    assert(timeB >= timeA);

    while(time >= (timeA / TIME_H) and time <= (timeB / TIME_H)) {
        loop();
    }
}

double Simulation::timeMS() const {
    return (time * TIME_H);
}

double Simulation::getSimulationTime() const {
    return time;
}

std::vector<double> Simulation::getNeuronV() const {
    return neuron->getMembraneV();
}
