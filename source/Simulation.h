//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_SIMULATION_H
#define BRUNEL_SIMULATION_H

#include "Neuron.h"
#include "Current.h"

class Simulation {
public:
    Simulation();
    void TimeIncrement() const;
    void loop();
    void run(double timeA, double timeB);

    // getters
    double getSimulationTime() const;

private:
    double time; // time is in milliseconds
    int time_h = 10; // time variable h that we will add at each incrementation

    Current* inCurrent; // we consider it constant but can make a function later on (dependant of time)
    Neuron* neuron; // for week 1 we simulate only one neuron


};


#endif //BRUNEL_SIMULATION_H
