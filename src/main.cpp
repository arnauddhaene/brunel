//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"
#include <fstream>
#include <iostream>

    /*!
     * @brief writes date into files
     *
     */
    void writeFiles(std::vector<Neuron*>* neurons, Simulation simulation);

    /*!
     * @brief in/out interface for simulation size input
     *
     */
    unsigned int IOSimSize();

    /*!
     * @brief in/out interface for current value in picoA
     *
     */
    double IOCurrentValue(unsigned int id);

    /*!
     * @brief in/out interface for current start and stop times
     *
     * @param boolean value determines start or stop value
     */
    unsigned long IOCurrentTime(bool start);

int main() {

    unsigned int size(IOSimSize());

    //! Simulation creation
    Simulation sim1(size);

    for(unsigned int i(0); i < size; ++i) {

        //! Current input interface at work
        sim1.setCurrent(IOCurrentValue(i), i, IOCurrentTime(true), IOCurrentTime(false));

    }

    //! Simulation run - times given in ms
    std::vector<Neuron*>* allneurons = sim1.run(0, 500);

    //! File writing
    writeFiles(allneurons, sim1);

    return 0;
}


void writeFiles(std::vector<Neuron*>* results, Simulation simulation) {

    //! Outputting file with simulation data

    std::cout << "Writing date to file" << ((results->size() > 1) ? "s :" : " :") << std::endl;

    for(unsigned int i(0); i < results->size(); ++i) {

        std::cout << "LOADING : " << i + 1 << "/" << results->size() << std::endl;

        std::vector<double> V(simulation.getNeuronV(i));

        std::ofstream outputFile;

        outputFile.open("Neuron" + std::to_string(i) + "_Potentials.txt");

        if (!V.empty()) {
            for (int j(0); j < V.size(); ++j) {
                outputFile << j * TIME_H << ":::" << V[j] << std::endl;
            }
        }

        outputFile.close();

    }

    std::cout << "Success. Visit Jupyter Notebook for plots." << std::endl;
}

unsigned int IOSimSize() {

    unsigned int size;

    std::cout << "Input simulation size (number of neurons) : " << std::endl;

    std::cin >> size;

    return size;

}

double IOCurrentValue(unsigned int id) {

    double value;

    std::cout << "Input external current value (picoA) for neuron " << id << " :" << std::endl;
    do {
        std::cin >> value;
        if (value < 0) {
            std::cout << "ERROR : please input positive value" << std::endl;
        }
    } while(value < 0);

    return value;

}

unsigned long IOCurrentTime(bool start) {

    unsigned long time;

    std::cout << "insert " << (start ? "start" : "stop") << " time (in ms) :" << std::endl;

    std::cin  >> time;

    return time; //! time was entered in ms - conversion is done afterwards

}