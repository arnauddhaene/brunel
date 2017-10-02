//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_SIMULATION_H
#define BRUNEL_SIMULATION_H

#include "Neuron.h"

class Simulation {
public:
    Simulation();
    void TimeIncrement() const;
    void NeuronLoop();

    // getters
    double getSimulationTime() const;

private:
    double time; // time is in milliseconds
    int time_h = 1; // time variable h that we will add at each incrementation


    double inCurrent; // we consider it constant but can make a function later on (dependant of time)
    double tau; // time constant - tau = RC
    double res; // resistance


    Neuron neuron; // for week 1 we simulate only one neuron


};


#endif //BRUNEL_SIMULATION_H
