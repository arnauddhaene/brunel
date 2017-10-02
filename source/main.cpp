//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"
#include <fstream>
#include <iostream>

int main() {

    Simulation sim1;
    sim1.run(0.2, 1.2);

    vector<double> V(sim1.getNeuronV());

    ofstream outputFile;
    outputFile.open("membranepotentials.txt");

    cout << "Writing date to file : neuron membrane potentials." << endl;

    outputFile << "The time incrementation between each measure is : " << sim1.getH() << endl;

    if(!V.empty()) {
        for(auto datapoint : V) {
            outputFile << datapoint << endl;
        }
    }

    outputFile.close();
    cout << " === > success\n";

    return 0;
}

