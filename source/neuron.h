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
    /*!
     * @brief Constructor
     *
     */
    Neuron();

    /*!
     * @brief Destructor
     *
     */
    ~Neuron() = default;

    /*!
     * @brief updates Neuron every ∆t
     *
     * @note time needed to timestamp eventual spikes
     */
    void update(double time, Current*);

    // Getters
    bool getRefractory() const;
    double getPotential() const;
    double getThreshold() const;
    double getRefTime() const;
    int getSpikesNumber() const;
    std::vector<double> getMembraneV() const;

    // Setters
    void setRefractory(bool);
    void setPotential(double);
    void setRefTime(double);

private:

    double membraneV; // membrane potential unique to each neuron
    bool refractory; // binary expressions shows if neuron is in refractory state or not

    double threshold; // potential threshold
    double tau; // time constant
    double res; // resistance

    std::vector<double> spikeTimes; // the times when the spikes occur (size of vector is number of spikes)
    std::vector<double> membranePotentials; // membrane potentials at each ∆t of the simulation

    double reftime; // refractory time remaining for neuron


};


#endif //BRUNEL_NEURON_H
