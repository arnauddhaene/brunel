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

    // Neuron 1

    std::vector<double> V1(sim1.getNeuronV(1));

    std::ofstream outputFile;
    outputFile.open("Neuron1_Potentials.txt");

    std::cout << "Writing date to file : neuron 1 membrane potentials." << std::endl;

    if(!V1.empty()) {
        for(int i(0); i < V1.size() ; ++i) {
            outputFile << i * TIME_H << ":::" << V1[i] << std::endl;
        }
    }

    outputFile.close();
    std::cout << "success. filename : Neuron1_Potentials.txt\n";


    // Neuron 2

    std::vector<double> V2(sim1.getNeuronV(2));

    std::ofstream outputFile2;
    outputFile2.open("Neuron2_Potentials.txt");

    std::cout << "Writing date to file : neuron 2 membrane potentials." << std::endl;


    if(!V2.empty()) {
        for(int i(0); i < V2.size() ; ++i) {
            outputFile2 << i * TIME_H << ":::" << V2[i] << std::endl;
        }
    }

    outputFile2.close();
    std::cout << "success. filename : Neuron2_Potentials.txt\n";

    return 0;
}

