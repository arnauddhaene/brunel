//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"
#include <fstream>
#include <iostream>

int main() {

    Simulation sim1;
    sim1.run(0.2, 1.2);

    std::vector<double> V(sim1.getNeuronV());

    std::ofstream outputFile;
    outputFile.open("membranepotentials.txt");

    std::cout << "Writing date to file : neuron membrane potentials." << std::endl;

    outputFile << "The time incrementation between each measure is : " << sim1.getH() << std::endl;

    outputFile << "Time (ms)" << "    " << "  V(t) " << std::endl;

    if(!V.empty()) {
        for(int i(0); i < V.size() ; ++i) {
            outputFile << i * sim1.getH() << "    " << V[i] << std::endl;
        }
    }

    outputFile.close();
    std::cout << " === > success\n";

    return 0;
}

