//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"
#include <fstream>
#include <iostream>

int main() {

    // simulation creation
    Simulation sim1;

    // running for 10 ms
    sim1.run(0, 10);

    // output file with data
    std::vector<double> V(sim1.getNeuronV());

    std::ofstream outputFile;
    outputFile.open("membranepotentials.txt");

    std::cout << "Writing date to file : neuron membrane potentials." << std::endl;

    outputFile << "The time incrementation between each measure is : " << TIME_H << std::endl;

    outputFile << "Time (ms)" << "    " << "  V(t) " << std::endl;

    if(!V.empty()) {
        for(int i(0); i < V.size() ; ++i) {
            outputFile << i * TIME_H << "       " << V[i] << std::endl;
        }
    }

    outputFile.close();
    std::cout << "=== success ===\n";

    return 0;
}

