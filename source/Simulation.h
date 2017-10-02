//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_SIMULATION_H
#define BRUNEL_SIMULATION_H

#include "Neuron.h"
#include <vector>
#include <cmath>
#include "constants.h"

class Simulation {
public:
    Simulation();
    void TimeIncrement();
    void loop(double timeA, double timeB);
    void run(double timeA, double timeB);

    // getters
    double getSimulationTime() const;
    std::vector<double> getNeuronV() const;

private:
    double time; // time is in milliseconds

    Current* inCurrent; // we consider it constant but can make a function later on (dependant of time)
    Neuron* neuron; // for week 1 we simulate only one neuron


};


#endif //BRUNEL_SIMULATION_H
