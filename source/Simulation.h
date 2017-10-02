//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_SIMULATION_H
#define BRUNEL_SIMULATION_H

#include "Neuron.h"
#include <vector>
#include <cmath>
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
    void loop(double timeA, double timeB);

    /*!
     * @brief runs Simulation from time A to time B
     *
     */
    void run(double timeA, double timeB);

    // Getters
    double getSimulationTime() const;
    std::vector<double> getNeuronV() const;

private:

    double time; // Simulation time - in ms

    Current* inCurrent; // Simulation's current
    Neuron* neuron; // Simulation's neuron

};


#endif //BRUNEL_SIMULATION_H
