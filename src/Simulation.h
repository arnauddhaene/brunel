//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_SIMULATION_H
#define BRUNEL_SIMULATION_H

#include "Neuron.h"
#include "constants.h"

/*!
 * @class Represents cortex simulation
 *
 * @brief Simulation contains neurons and associatied currents
 */
class Simulation {

public:
    /*!
     * @brief Constructor overload
     *
     * @note time automatically set to zero
     * @note connections generated only if size equal to 12500
     *
     * @param size simulation size is equal to number of neurons
     */
    explicit Simulation(unsigned int size);

    /*!
     * @brief Time Incrementer
     *
     */
    void TimeIncrement();

    /*!
     * @brief represents one loop (one time increment ∆t)
     *
     */
    void loop();

    /*!
     * @brief runs Simulation from time A to time B
     *
     * @param timeA start time
     * @param timeB stop time
     *
     * @return pointer on neuron vector for main program
     * to print out correct data
     */
    std::vector<Neuron*>* run(double timeA, double timeB);

    /*!
     * @brief converts from timesteps to ms
     *
     * @return simulation time in milliseconds (instead of timesteps)
     */
    double timeMS() const;

    /*!
     * @brief generates connections for entire simulation
     *
     * @param size of simulation ==> is supposed to be 12500
     */
    void generateConnections(unsigned int size);

    /*!
     *
     * @return simulation time in timesteps
     */
    unsigned long getSimulationTime() const;

    /*!
     * @param neuron ID
     *
     * @return neuron potential vector
     */
    std::vector<double> getNeuronV(unsigned int) const;

    /*!
     * @param id ID of wanted current
     * @param time time of wanted current value
     *
     * @return current value
     */
    double getCurrent(unsigned int id, unsigned long time) const;

    /*!
     * @param id neuron ID
     *
     * @return pointer on wanted neuron
     */
    Neuron* getNeuron(unsigned int id) const;

    /*!
     * @brief sets current
     *
     * @param val current value
     * @param id ID of current (same as neuron's ID)
     * @param sta start time in timesteps
     * @param sto stop time in timesteps
     */
    void setCurrent(double val, unsigned int id, unsigned long sta, unsigned long sto);

private:
    unsigned long time; //! Simulation time - in timesteps

    std::vector<Current*> currents; //! Simulation's currents

    std::vector<Neuron*> neurons; //! Simulation's neurons

};


#endif //BRUNEL_SIMULATION_H
