//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_SIMULATION_H
#define BRUNEL_SIMULATION_H

#include "Neuron.h"
#include <vector>

class Simulation {
public:
    Simulation();
    void TimeIncrement();
    void loop(double timeA, double timeB);
    void run(double timeA, double timeB);

    // getters
    double getSimulationTime() const;
    std::vector<double> getNeuronV() const;
    double getH() const; // in order to know the incrementation of time

private:
    double time; // time is in milliseconds
    double time_h = 10; // time variable h that we will add at each incrementation

    Current* inCurrent; // we consider it constant but can make a function later on (dependant of time)
    Neuron* neuron; // for week 1 we simulate only one neuron


};


#endif //BRUNEL_SIMULATION_H
