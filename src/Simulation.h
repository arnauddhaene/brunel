//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_SIMULATION_H
#define BRUNEL_SIMULATION_H

#include "Neuron.h"
#include "Current.h"
#include <vector>
#include <cmath>
#include "constants.h"
#include <cassert>

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
     */
    void run(double timeA, double timeB);

    /*!
     * @brief converts from timesteps to ms
     *
     */
    double timeMS() const;

    // Getters
    double getSimulationTime() const;
    std::vector<double> getNeuronV() const;

private:

    unsigned long time; // Simulation time - in TIMESTEPS

    Current* inCurrent; // Simulation's current

    Neuron* neuron; // Simulation's neuron

};


#endif //BRUNEL_SIMULATION_H
