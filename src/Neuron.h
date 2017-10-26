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
     * @param time simulation time
     * @param currents simulation currents
     * @param neurons simulation neurons
     *
     * @note time needed to timestamp eventual spikes
     */
    void update(unsigned long time, std::vector<Current*>* currents, std::vector<Neuron*>* neurons);

    /*!
     * @brief updates Neuron's attributes when spike occurs
     *
     * @param time simulation time
     * @param neurons simulation neurons
     */
    void spike(unsigned long time, std::vector<Neuron*>* neurons);

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
     * @param takes time in timesteps
     * @param current pointer on neuron's current
     */
    void solveODE(unsigned long time, Current* current);

    /*!
     * @brief stores membrane potential
     *
     */
    void storeV();

    /*!
     * @brief what happens to a neuron when he receives a spike
     *
     * @note time needed to access buffer queue
     *
     * @param time is current time
     */
    void receiveSpike(unsigned long time);

    /*!
     * @brief Increments the neuron's local Clock
     *
     */
    void ClockIncrement();

    /*!
    * @brief get neuron state
     *
    * @return true if refractory, false if not
    */
    bool isRefractory() const;

    /*!
    * @brief get neuron potential
     *
    * @return membrane potential in mV
    */
    double getPotential() const;

    /*!
     *
     * @return refractory time remaining in timesteps
     */
    unsigned long getRefTime() const;

    /*!
     *
     * @return spike numbers since beginning of simulation run
     */
    int getSpikesNumber() const;

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
    std::vector<double> getMembraneV() const;

    /*!
     *
     * @param time simulation time
     *
     * @return membrane potential of given time
     */
    double getMembraneV(unsigned int time) const;

    /*!
     *
     * @return pointer on neuron's buffer
     */
    Buffer* getBuffer() const;

    /*!
     * @brief Type of Neuron : excitatory or inhibitory
     * @return neuron type
     */
    bool isExcitatory() const;

    /*!
     * @brief sets state to : true - refractory, false - normal
     *
     * @param state of neuron
     */
    void setRefractory(bool state);

    /*!
     * @brief sets potential to given value
     *
     * @param v potential in mV
     */
    void setPotential(double v);

    /*!
     * @brief sets refractory period
     *
     * @param time refractory period in timesteps
     */
    void setRefTime(unsigned long time);

    /*!
     * @brief adds connection to connections vector during initialisation
     *
     * @param id of connecting neuron
     */
    void addConnection(unsigned int id);


private:
    double membraneV; //! membrane potential unique to each neuron

    bool refractory; //! binary expressions shows if neuron is in refractory state or not

    std::vector<unsigned long> spikeTimes; //! the times when the spikes occur (size of vector is number of spikes)

    std::vector<double> membranePotentials; //! membrane potentials at each ∆t of the simulation

    std::vector<unsigned int> connections; //! IDs of connected neurons (those who will receive his signals)

    unsigned long reftime; //! refractory time remaining for neuron

    unsigned long clock; //! local clock used by neuron

    unsigned int ID; //! neuron identification (number in neurons vector in Simulation class) - can not change

    Buffer* buffer; //! Ring buffer association to neuron

    bool type; //! Type of neuron : Excitatory - true, Inhibitory - false

};


#endif //BRUNEL_NEURON_H
