//
// Created by Arnaud Dhaene on 30.10.17.
//

#include "Experiment.h"
#include <fstream>
#include <ostream>

Experiment::Experiment(const std::string & name)
        : network(new Network(C::SIMULATION_SIZE, false, false, true, true ,true)), filename(name)
{}

void Experiment::saveSpikes(std::vector<Neuron *> neurons) const {

    /// Outputting file with simulation data

    std::cout << "saving..." << '\n';

    std::ofstream outputFile;

    outputFile.open(filename);

    /// We are only taking 50 of the 12500 neurons

    unsigned int divider(12500 / 50);

    for(unsigned int i(0); i < neurons.size(); i += divider) {

        assert(!neurons[i]->getSpikes().empty());

        for(unsigned long spike : neurons[i]->getSpikes()) {

            outputFile << spike * C::TIME_H << '\t' << i / divider   << '\n';

        }
    }

    outputFile.close();

    std::cout << "Success. Visit Jupyter Notebook for plot." << '\n';

}

void Experiment::savePotentials(const std::vector<Neuron *>& results, const Network & simulation) const {

    /// Outputting file with simulation data

    std::cout << "Writing date to file" << ((results.size() > 1) ? "s :" : " :") << '\n';

    for(unsigned int i(0); i < results.size(); ++i) {

        std::cout << "LOADING : " << i + 1 << "/" << results.size() << '\n';

        std::vector<double> V(simulation.getNeuronV(i));

        std::ofstream outputFile;

        outputFile.open("Neuron" + std::to_string(i) + "_Potentials.txt");

        if (!V.empty()) {
            for (int j(0); j < V.size(); ++j) {
                outputFile << j * C::TIME_H << ":::" << V[j] << '\n';
            }
        }

        outputFile.close();

    }

    std::cout << "Success. Visit Jupyter Notebook for plots." << '\n';
}

unsigned int Experiment::IOSimSize() const {

    unsigned int size;

    std::cout << "Input simulation size (number of neurons) : " << '\n';

    std::cin >> size;

    return size;

}

double Experiment::IOCurrent(unsigned int id) const {

    double value;

    std::cout << "Input external current value (picoA) for neuron " << id << " :" << '\n';
    do {
        std::cin >> value;
        if (value < 0) {
            std::cout << "ERROR : please input positive value" << '\n';
        }
    } while(value < 0);

    return value;

}

unsigned long Experiment::IOTime(bool start) const {

    unsigned long time;

    std::cout << "insert " << (start ? "start" : "stop") << " time (in ms) :" << '\n';

    std::cin  >> time;

    return time; //! time was entered in ms - conversion is done afterwards

}

void Experiment::displayMean(std::vector<Neuron*> results) const {

    double mean(0);

    for(auto neuron : results) {
        mean += neuron->getSpikes().size();
    }

    std::cout << "Average spike number : " << mean / results.size() << '\n';
}

void Experiment::run(unsigned long time) {

    /*
     * Simulation run
     * time in ms
     */
    std::vector<Neuron*> results = network->run(time);

    /// Raster plot
    saveSpikes(results);

    /// Information display
    displayMean(results);

    network->reset();

}