//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_NEURON_H
#define BRUNEL_NEURON_H

#include "Current.h"
#include "Buffer.h"
#include <cmath>
#include "constants.h"
#include <iostream>
#include <random>

/*!
 * @class represents a Neuron
 *
 */
class Neuron {

public:
    /*!
     * @brief Constructor
     *
     * @param id neuron identification number
     * @param neuron type : excitatory on inhibitory
     *
     * @note ID in neurons vector will identify neuron during whole simulation
     */
    Neuron(unsigned int id, bool type);

    /*!
     * @brief Destructor
     *
     */
    ~Neuron() = default;

    /*!
     * @brief updates Neuron every ∆t
     *
     * @param currents simulation currents
     * @param neurons simulation neurons
     * @param membrane tells neuron to store potential during time
     * @param spikes tells neuron to store spikes over time
     * @param poisson tells neuron if there is background noise
     *
     * @note time needed to timestamp eventual spikes
     */
    void update(std::vector<Current*>* currents, std::vector<Neuron*>* neurons,
                bool membrane, bool spikes, bool poisson, bool current);

    /*!
     * @brief updates Neuron's attributes when spike occurs
     *
     * @param neurons simulation neurons
     */
    void spike(std::vector<Neuron*>* neurons, bool spikes);

    /*!
     * @brief updates Neuron's attributes when in refractory state
     *
     */
    void updateRefractory();

    /*!
     * @brief resolves ODE differential equation
     *
     * @note directly sets Potential
     *
     * @param current pointer on neuron's current
     * @param tells neuron if there is background noise
     */
    void solveODE(Current* current, bool poisson);

    /*!
     * @brief stores membrane potential
     *
     */
    void storePotential();

    /*!
     * @brief what happens to a neuron when he receives a spike
     *
     * @note time needed to access buffer queue
     *
     * @param excitatory type of neuron sending spike
     */
    void receiveSpike(bool excitatory);


    /*!
     * @brief simulation data in order to create raster plot
     * @return vector of spike times
     */
    std::vector<unsigned long> getSpikes() const;

    /*!
     * @brief Data of membrane potential throughout time
     *
     * @return vector of membrane potentials dependant on time (index)
     */
    std::vector<double> getPotentials() const;

    /*!
     *
     * @return pointer on neuron's buffer
     */
    Buffer* getBuffer() const;

    /*!
     * @brief adds connection to connections vector during initialisation
     *
     * @param id of connecting neuron
     */
    void addConnection(unsigned int id);

private:
    unsigned long reftime, clock; //! refractory time remaining for neuron and local clock used by neuron

    double potential; //! membrane potential unique to each neuron

    bool refractory, excitatory; //! state and type of neuron

    std::vector<unsigned long> spikeTimes; //! the times when the spikes occur (size of vector is number of spikes)

    std::vector<double> membranePotentials; //! membrane potentials at each ∆t of the simulation

    std::vector<unsigned int> connections; //! IDs of connected neurons (those who will receive his signals)

    unsigned int ID; //! neuron identification (number in neurons vector in Simulation class) - can not change

    Buffer* buffer; //! Ring buffer association to neuron

    static double c1, c2;
};


#endif //BRUNEL_NEURON_H
