//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_SIMULATION_H
#define BRUNEL_SIMULATION_H

#include "Neuron.h"
#include "constants.h"

/*!
 * @brief represents a neural network
 *
 */
class Network {
public:
    /*!
     * @brief Constructor
     *
     * @note time automatically set to zero
     * @note bools have default values if nothing is put in during construction
     * @note if connections == true, 1250 connections are generated for every neuron regardless of simulation size
     * @note default boolean values correspond to brunel paper simulation
     *
     * @param size simulation size is equal to number of neurons
     * @param current tells simulation to use current or not
     * @param membrane tells simulation to store membrane potentials or not
     * @param spikes tells simulation to store spike times or not
     * @param poisson tells simulation to add background noise or not
     * @param connections tells simulation to generate random connections or not
     *
     * @note marked explicit as callable with single argument
     */
     explicit Network(unsigned int size, bool current = false, bool membrane = false,
                    bool spikes = true, bool poisson = true, bool connections = true);

    /*!
     * @brief destructor to remove allocations
     */
    virtual ~Network();

    /*!
     * @brief represents one loop (one time increment ∆t)
     */
    void loop();

    /*!
     * @brief runs Simulation from time A to time B
     *
     * @param endT stop time
     *
     * @return pointer on neuron vector
     */
    std::vector<Neuron*> run(double endT);


    /*!
     * @brief generates connections for entire simulation
     */
    void generateConnections();


    /*!
     * @param id neuron identification number
     *
     * @return neuron potential vector
     */
    std::vector<double> getNeuronV(unsigned int id) const;

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
     * @brief sets current of specific neuron
     *
     * @param value of current
     * @param id ID of current (same as neuron's ID)
     * @param start time in timesteps
     * @param stop time in timesteps
     */
    void setCurrent(double value, unsigned int id, unsigned long start, unsigned long stop);

    /*!
     * @brief resets network to initial conditions
     */
    void reset();

    /*!
     * @brief random background noise generator
	 *
	 * @note use of mt19937 generator to express poisson distribution
     *
     * @return value in mV of background noise
	 */
    static double getNoise() {

        /// random device
        static std::random_device randomDevice;

        /// random generator
        static std::mt19937 gen(randomDevice());

        /// poisson distribution
        static std::poisson_distribution<> poisson(C::NU_EXT);

        /// background noise will be the number of random spikes multiplied by J
        return (double) poisson(gen) * C::J_AMP_EXCITATORY * C::TIME_H;
    }

    /*!
     * @brief static network clock
     */
    static unsigned long clock; //! Simulation time - in timesteps

private:

    bool current, membrane, spikes, poisson; // Simulation's conditions

    std::vector<Neuron*> neurons; //! Simulation's neurons

    std::vector<Current*> currents; //! Simulation's currents

};


#endif //BRUNEL_SIMULATION_H
