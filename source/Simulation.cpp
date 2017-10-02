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

    neuron.update(getSimulationTime());

    TimeIncrement(); // increments time
}

void Simulation::run(double timeA, double timeB) {

}

// getters
double Simulation::getSimulationTime() const {
    return time;
}