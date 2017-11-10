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
     * @param type excitatory (true) or inhibitory
     *
     * @note marked explicit to avoid unintentional implicit conversions
     */
     explicit Neuron( bool type );

    /*!
     * @brief Destructor
     *
     */
    ~Neuron() = default;

    /*!
     * @brief updates Neuron every ∆t
     *
     * @param membrane tells neuron to store potential during time
     * @param spikes tells neuron to store spikes over time
     * @param poisson value of background noise in mV
     * @param current value in pA
     *
     * @return spiking event during call to update
     */
    bool update( bool membrane, bool spikes, double poisson, double current );

    /*!
     * @brief adds spike transmission to buffer
     *
     * @param t network clock
     * @param transmission value of transmitted spike
     */
    void receiveSpike( unsigned long t, double transmission );

    /*!
     * @brief spiking data
     *
     * @return vector of spike times
     */
    std::vector<unsigned long> getSpikes() const;

    /*!
     * @brief data of membrane potential throughout time
     *
     * @return vector of membrane potentials dependant on time in timesteps (index)
     */
    std::vector<double> getPotentials() const;

    /*!
     * @brief adds connection to connections vector
     *
     * @param id of connecting neuron - index in master Neuron* vector
     */
    void addConnection( unsigned int id );

    /*!
     * @brief get a list of neuron's connections
	 *
	 *  @return reference on connections
	 */
    const std::vector<unsigned int> & getConnections() const;

    /*!
     * @return type of neuron
     */
    bool isExcitatory() const;

    /*!
     * @brief returns the amplitude according to the time
     *
     * @param time simulation time
     *
     * @note returns 0 if there is no attributed spike transmission
     *
     * @return amplitude of transmitted spike in mV
     */
    double b_amplitude( unsigned long time ) const;

private:
    /*!
     * @brief updates Neuron's attributes when spike occurs
     */
    void spike();

    /*!
     * @brief resolves ODE differential equation
     *
     * @note directly sets Potential
     *
     * @param current current value
     * @param poisson background noise
     */
    void solveODE( double current, double poisson );

    /*!
     * @brief adds a Spike Transmission into buffer queue
     *
     * @param time current time
     */
    void b_erase( unsigned long time );

    unsigned long mClock; //! time

    double mPotential; //! membrane potential unique to each neuron

    bool mExcitatory; //! type of neuron

    std::array<double, C::DELAY + 1> mBuffer; //! Neuron's buffer

    std::vector<unsigned long> mSpikeTimes; //! the times when the spikes occur

    std::vector<unsigned int> mConnections; //! outgoing connections

    std::vector<double> mMembranePotentials; //! membrane potentials at each ∆t of the simulation

    static double c1, c2; //! integration constants
};


#endif //BRUNEL_NEURON_H
