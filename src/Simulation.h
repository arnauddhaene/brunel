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
     * @brief Constructor
     *
     * @note Time automatically set to zero
     */
    Simulation();

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

private:

    unsigned long time; //! Simulation time - in TIMESTEPS

    std::vector<Current*> currents; //! Simulation's currents

    std::vector<Neuron*> neurons; //! Simulation's neurons


};


#endif //BRUNEL_SIMULATION_H
