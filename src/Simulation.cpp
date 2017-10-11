//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"

Simulation::Simulation() : time(0) {

    //! Neuron vector and Current pointer creation
    unsigned int size;

    std::cout << "Input simulation size (number of neurons) :" << std::endl;
    do {
        std::cin >> size;
        if (size < 0) {
            std::cout << "ERROR : please input positive value" << std::endl;
        }
    } while(size < 0);

    for(unsigned int i(0); i < size; ++i) {
        neurons.push_back(new Neuron(i)); //! here, i is the neuron's ID
        currents.push_back(new Current(i)); //! same for the currents
    }

}

void Simulation::TimeIncrement() {
    //! Time incrementation
    ++time;
}

void Simulation::loop() {

    //! Neuron update
    for(unsigned int i(0); i < neurons.size(); ++i) {

        neurons[i]->update(getSimulationTime(), &currents, &neurons);

    }

    //! Increments time
    TimeIncrement();
}

std::vector<Neuron*>* Simulation::run(double timeA, double timeB) {

    assert(timeA >= 0);
    assert(timeB >= timeA);

    while(time >= (timeA / TIME_H) and time <= (timeB / TIME_H)) {
        loop();
    }

    return &neurons;
}

double Simulation::timeMS() const {
    return (time * TIME_H);
}

unsigned long Simulation::getSimulationTime() const {
    return time;
}

std::vector<double> Simulation::getNeuronV(unsigned int ID) const {
    return neurons[ID]->getMembraneV();
}
