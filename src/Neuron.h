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
     * @note ID in neurons vector will identify neuron during whole simulation
     */
    Neuron(unsigned int);

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
    void update(double time, const Current& inC, Neuron& conneur);

    /*!
     * @brief what happens to a neuron when he recieves a spike
     *
     * @note time needed to timestamp eventual spikes
     */
    void recieveSpike(double amplitude);

    // Getters
    bool getRefractory() const;
    double getPotential() const;
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

    std::vector<double> spikeTimes; // the times when the spikes occur (size of vector is number of spikes)
    std::vector<double> membranePotentials; // membrane potentials at each ∆t of the simulation

    // std::vector<unsigned int> connections; // IDs of connected neurons

    double reftime; // refractory time remaining for neuron
    unsigned long clock; // local clock used by neuron

    unsigned int ID; // neuron identification (number in neurons vector in Simulation class) - can not change

    double buffer; // potential amplitude value than neuron recieved

};


#endif //BRUNEL_NEURON_H
