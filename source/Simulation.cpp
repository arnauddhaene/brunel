//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"
#include <cmath>


Simulation::Simulation() : time(0) {}

void Simulation::TimeIncrement() const {
    time += time_h;
}

void Simulation::loop() {

    neuron->update(getSimulationTime(), inCurrent);

    TimeIncrement(); // increments time
}

void Simulation::run(double timeA, double timeB) {

    while(time >= timeA and time <= timeB) {
        loop();
    }

}

// getters
double Simulation::getSimulationTime() const {
    return time;
}

vector<double> Simulation::getNeuronV() const {
    return neuron->getMembraneV();
}

double Simulation::getH() const {
    return time_h;
}