//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_NEURON_H
#define BRUNEL_NEURON_H


#include <vector>
#include "Current.h"
#include <cmath>
#include "constants.h"

enum State { active, inactive, refractory, MAXnSTATE };

class Neuron {

public:
    Neuron();
    ~Neuron() = default;
    void update(double time, Current*);
    void updateState();

    // getters
    State getState() const;
    double getPotential() const;
    double getThreshold() const;
    int getSpikesNumber() const;
    std::vector<double> getMembraneV() const;

    // setters
    void setState(State);
    void setPotential(double);

private:
    State nState; // identifies neuron state

    double membraneV; // membrane potential unique to each neuron

    double threshold; // potential threshold
    double tau; // time constant : tau = RC
    double res; // resistance

    std::vector<double> spikeTimes; // the times when the spikes occur (size of vector will be number of spikes
    std::vector<double> membranePotentials; // membrane potentials at each step of time of the simulation

    double reftime; // time it needs to stay in refractory - set at REFPERIOD when it's set to refractory


};


#endif //BRUNEL_NEURON_H
