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

class Neuron {

public:
    /*!
     * @brief Constructor
     * @param neuron ID, neuron type
     * @note ID in neurons vector will identify neuron during whole simulation
     */
    Neuron(unsigned int, bool);

    /*!
     * @brief Destructor
     *
     */
    ~Neuron() = default;

    /*!
     * @brief updates Neuron every ∆t
     * @param simulation time, currents and neurons
     * @note time needed to timestamp eventual spikes
     */
    void update(unsigned long time, std::vector<Current*>* allcurrents, std::vector<Neuron*>* allneurons);

    /*!
     * @brief updates Neuron's attributes when spike occurs
     *
     * @param current time, simulation neurons
     */
    void spike(unsigned long time, std::vector<Neuron*>* allneurons);

    /*!
     * @brief updates Neuron's attributes when in refractory state
     *
     *
     */
    void updateRefractory();

    /*!
     * @brief resolves ODE differential equation
     * @note directly sets Potential
     * @param takes time in timesteps, pointer on current
     */
    void solveODE(unsigned long, Current*);

    /*!
     * @brief stores membrane potential
     *
     */
    void storeV();

    /*!
     * @brief what happens to a neuron when he recieves a spike
     *
     * @note time needed to access buffeer queue
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
    * @brief get neuron stat
    * @return true if refractory, false if not
    */
    bool getRefractory() const;

    /*!
    * @brief get neuron potential
    * @return membrane potential in mV
    */
    double getPotential() const;

    /*!
     *
     * @return refractory time remaining in timesteps
     */
    double getRefTime() const;

    /*!
     *
     * @return spike numbers since beginning of simulation run
     */
    int getSpikesNumber() const;

    /*!
     * @brief Data of membrane potential throughout time
     * @return vector of membrane potentials dependant on time (index)
     */
    std::vector<double> getMembraneV() const;

    /*!
     *
     * @param i time
     * @return membrane potential of given time
     */
    double getMembraneV(unsigned int i) const;
    Buffer* getBuffer() const;

    /*!
     * @brief Type of Neuron : excitatory or inhibitory
     * @return neuron type
     */
    bool isExcitatory() const;

    /*!
     * @brief sets state to : true - refractory, false - normal
     */
    void setRefractory(bool);

    /*!
     * @brief sets potential to given value
     * @param potential in mV
     */
    void setPotential(double);

    /*!
     * @brief sets refractory period
     * @param refractory period in timesteps
     */
    void setRefTime(unsigned long);

    /*!
     * @brief adds connection to connections vector during initialisation
     * @param ID of connecting neuron
     */
    void addConnection(unsigned int);

private:

    double membraneV; //! membrane potential unique to each neuron
    bool refractory; //! binary expressions shows if neuron is in refractory state or not

    std::vector<unsigned long> spikeTimes; //! the times when the spikes occur (size of vector is number of spikes)
    std::vector<double> membranePotentials; //! membrane potentials at each ∆t of the simulation

    std::vector<unsigned int> connections; //! IDs of connected neurons (those who will receive his signals)

    double reftime; //! refractory time remaining for neuron
    unsigned long clock; //! local clock used by neuron

    unsigned int ID; //! neuron identification (number in neurons vector in Simulation class) - can not change

    Buffer* buffer; //! buffer

    bool type; //!

};


#endif //BRUNEL_NEURON_H
