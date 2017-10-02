//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_NEURON_H
#define BRUNEL_NEURON_H


#include <vector>
#include "Current.h"
#include <cmath>
#include "constants.h"

enum State { inactive, refractory };

class Neuron {

public:
    Neuron();
    ~Neuron() = default;
    void update(double time, Current*);
    void updateState();

    // getters
    bool getRefractory() const;
    double getPotential() const;
    double getThreshold() const;
    int getSpikesNumber() const;
    std::vector<double> getMembraneV() const;

    // setters
    void setRefractory(bool);
    void setPotential(double);

private:

    double membraneV; // membrane potential unique to each neuron
    bool refractory; // binary expressions shows if neuron is in refractory state or not

    double threshold; // potential threshold
    double tau; // time constant : tau = RC
    double res; // resistance

    std::vector<double> spikeTimes; // the times when the spikes occur (size of vector will be number of spikes
    std::vector<double> membranePotentials; // membrane potentials at each step of time of the simulation

    double reftime; // time it needs to stay in refractory - set at REFPERIOD when it's set to refractory


};


#endif //BRUNEL_NEURON_H
