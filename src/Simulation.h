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
     */
    void run(double timeA, double timeB);

    /*!
     * @brief converts from timesteps to ms
     *
     */
    double timeMS() const;

    // Getters
    unsigned long getSimulationTime() const;
    std::vector<double> getNeuronV(unsigned int) const;

private:

    unsigned long time; // Simulation time - in TIMESTEPS

    Current* inCurrent; // Simulation's current
    Current* inCurrent1; // current for 2nd neuron

    // std::vector<Current*> currents; // Simulation's currents

    // std::vector<Neuron*> neurons; // Simulation's neurons

    Neuron* neuron1;
    Neuron* neuron2;

};


#endif //BRUNEL_SIMULATION_H
