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
 * Simulation contains neurons and a current
 *
 */
class Simulation {
public:

    /*!
     * @brief Constructor overload
     *
     * @note Time automatically set to zero
     * @param simulation size is equal to number of neurons
     */
    Simulation(unsigned int size);

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
     * @returns pointer on neuron vector for main program
     * to print out correct data
     */
    std::vector<Neuron*>* run(double timeA, double timeB);

    /*!
     * @brief converts from timesteps to ms
     *
     */
    double timeMS() const;

    //! Getters
    unsigned long getSimulationTime() const;
    std::vector<double> getNeuronV(unsigned int) const;
    double getCurrent(unsigned int, unsigned long) const;
    Neuron* getNeuron(unsigned int) const;

    //! Setters
    void setCurrent(double val, unsigned int id, unsigned long sta, unsigned long sto);

private:

    unsigned long time; //! Simulation time - in TIMESTEPS

    std::vector<Current*> currents; //! Simulation's currents

    std::vector<Neuron*> neurons; //! Simulation's neurons


};


#endif //BRUNEL_SIMULATION_H
