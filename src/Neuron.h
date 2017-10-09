//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_NEURON_H
#define BRUNEL_NEURON_H

#include "Current.h"
#include "Buffer.h"
#include <cmath>
#include "constants.h"


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
    void update(unsigned long time, const Current& inC, Neuron& conneur);

    /*!
     * @brief updates Neuron's attributes when spike occurs
     *
     *
     */
    void spike(unsigned long time, Neuron& conneur);

    /*!
     * @brief updates Neuron's attributes when in refractory state
     *
     *
     */
    void updateRefractory();

    /*!
     * @brief resolves ODE differential equation
     *
     * @note directly sets Potential
     * @param takes time in timesteps, current pointer
     */
    void solveODE(unsigned long, const Current&);

    /*!
     * @brief stores membrane potential
     *
     */
    void storeV();

    /*!
     * @brief what happens to a neuron when he recieves a spike
     *
     * @note time needed to timestamp eventual spikes
     */
    void recieveSpike(SpikeTransmission);

    /*!
     * @brief Increments the neuron's local Clock
     *
     */
    void ClockIncrement();

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

    std::vector<unsigned long> spikeTimes; // the times when the spikes occur (size of vector is number of spikes)
    std::vector<double> membranePotentials; // membrane potentials at each ∆t of the simulation

    // std::vector<unsigned int> connections; // IDs of connected neurons

    double reftime; // refractory time remaining for neuron
    unsigned long clock; // local clock used by neuron

    unsigned int ID; // neuron identification (number in neurons vector in Simulation class) - can not change

    Buffer* buffer; // buffer

};


#endif //BRUNEL_NEURON_H
