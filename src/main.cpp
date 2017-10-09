//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"
#include <fstream>
#include <iostream>

int main() {

    // Simulation creation
    Simulation sim1;

    // Simulation run - times given in ms
    sim1.run(0, 500);

    // Outputting file with simulation data
    std::vector<double> V(sim1.getNeuronV());

    std::ofstream outputFile;
    outputFile.open("Neuron_Potentials.txt");

    std::cout << "Writing date to file : neuron membrane potentials." << std::endl;

    outputFile << "SIMULATION : Neuron membrane potential over time " << TIME_H << std::endl << std::endl;

    outputFile << "The time incrementation between each measure is : " << TIME_H << " ms" << std::endl;

    outputFile << "Total simulation time : " << V.size() * TIME_H << " ms" << std::endl << std::endl;

    outputFile << "Time (ms) \t V (mV) " << std::endl;

    if(!V.empty()) {
        for(int i(0); i < V.size() ; ++i) {
            outputFile << i * TIME_H << "\t\t" << V[i] << std::endl;
        }
    }

    outputFile.close();
    std::cout << "success. filename : Neuron_Potentials.txt\n";

    return 0;
}

