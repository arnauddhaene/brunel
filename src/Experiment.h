//
// Created by Arnaud Dhaene on 30.10.17.
//

#ifndef BRUNEL_EXPERIMENT_H
#define BRUNEL_EXPERIMENT_H

#include "constants.h"
#include "Network.h"
#include <string>

/*!
 * @brief represents experiment
 *
 * handles input/output, file saving and running the network
 */
class Experiment {

public:
    /*!
     * @brief Constructor
     *
     * @param filename of to be saved file
     */
    explicit Experiment(const std::string & filename);

    /*!
     * @brief writes date into files
     */
    void savePotentials(const std::vector<Neuron*> & neurons, const Network& simulation);

    /*!
     * @brief in/out interface for simulation size input
     *
     */
    unsigned int IOSimSize();

    /*!
     * @brief in/out interface for current value in picoA
     *
     */
    double IOCurrent(unsigned int id);

    /*!
     * @brief in/out interface for current start and stop times
     *
     * @param boolean value determines start or stop value
     */
    unsigned long IOTime(bool start);

    /*!
     * @brief outputs raster plot information into a txt file
     * @param neurons simulation's neurons in which the information concerning the spikes is stored
     */
    void saveSpikes(std::vector<Neuron *> neurons);

    /*!
     * @brief displays average total spikes per neuron
     *
     * @param results vector of pointers on neurons with stored spikes
     */
    void displayMean(std::vector<Neuron*> results);

    /*!
     * @brief runs the experiment <-> one network simulation
     *
     * @param time total simulation time of network in experiment
     */
    void run(unsigned long time);

private:
    Network* network;

    std::string filename;

};


#endif //BRUNEL_EXPERIMENT_H
