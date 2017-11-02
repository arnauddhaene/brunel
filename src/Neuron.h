//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_NEURON_H
#define BRUNEL_NEURON_H

#include "Current.h"
#include <cmath>
#include "constants.h"
#include <iostream>
#include <random>
#include <array>

/*!
 * @brief represents a neuron
 *
 */
class Neuron {

public:
    /*!
     * @brief Constructor
     *
     * @param neuron type : excitatory on inhibitory
     *
     * @note ID in neurons vector will identify neuron during whole simulation
     */
    Neuron(bool type);

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
     * @param current tells neuron if we are using current or not
     *
     * @note time needed to timestamp eventual spikes
     *
     * @return did the neuron spike or not ?
     */
    bool update(bool membrane, bool spikes, bool poisson, double current);

    /*!
     * @brief updates Neuron's attributes when spike occurs
     *
     * @param neurons simulation neurons
     */
    void spike(bool spikes);

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
     * @param current current value
     * @param poisson background noise
     */
    void solveODE(double current, double poisson);

    /*!
     * @brief what happens to a neuron when he receives a spike
     *
     * @param transmission value of transmitted spik
     * @param t network clock
     */
    void receiveSpike(unsigned long t, double transmission);

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
     * @brief adds connection to connections vector during initialisation
     *
     * @param id of connecting neuron
     */
    void addConnection(unsigned int id);

    /*!
     * @brief adds a Spike Transmission into buffer queue
     *
     * @param time corresponding to appropriate spike transmission
     * @param transmission value of transmission
     */
    void b_addTransmission(unsigned long time, double transmission);

    /*!
     * @brief adds a Spike Transmission into buffer queue
     *
     * @param current time
     */
    void b_erase(unsigned long time);

    /*!
     * @brief returns the amplitude according to the time
     *
     * @param time simulation time
     *
     * @note returns 0 if there is no attributed spike transmission
     *
     * @return amplitude of transmitted spike in mV
     */
    double b_amplitude(unsigned long time) const;

    /*!
     * @brief returns index of buffer in which to write
     *
     * @param current time
     *
     * @return index corresponding to given time
     */
    unsigned int b_index(unsigned long time) const;

    /*! @brief get a list of neuron's connections
	 *
	 *  @return reference on connections
	 */
    const std::vector<unsigned int>& getConnections() const;

    /*!
     *
     * @return type of neuron
     */
    bool isExcitatory() const;

private:
    unsigned long reftime, clock; //! refractory time remaining for neuron and local clock used by neuron

    double potential; //! membrane potential unique to each neuron

    bool refractory, excitatory; //! state and type of neuron

    std::array<double, C::DELAY + 1> buffer; //! Neuron's buffer

    std::vector<unsigned long> spikeTimes; //! the times when the spikes occur (size of vector is number of spikes)

    std::vector<unsigned int> connections; //! IDs of connected neurons (those who will receive his signals)

    std::vector<double> membranePotentials; //! membrane potentials at each ∆t of the simulation

    static double c1, c2; //! integration constants
};


#endif //BRUNEL_NEURON_H
