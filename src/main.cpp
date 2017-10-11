//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"
#include <fstream>
#include <iostream>

int main() {

    //! Simulation creation
    Simulation sim1;

    //! Simulation run - times given in ms
    std::vector<Neuron*>* allneurons = sim1.run(0, 500);

    //! Outputting file with simulation data

    std::cout << "Writing date to file" << ((allneurons->size() > 1) ? "s :" : " :") << std::endl;

    for(unsigned int i(0); i < allneurons->size(); ++i) {

        std::cout << "LOADING : " << i + 1 << "/" << allneurons->size() << std::endl;

        std::vector<double> V(sim1.getNeuronV(i));

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



    return 0;
}

