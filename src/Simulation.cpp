//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"

Simulation::Simulation() : time(0) {
    /*
     * // Neuron vector and Current pointer creation
    unsigned int size;

    std::cout << "Input simulation size (number of neurons) :" << std::endl;
    do {
        std::cin >> size;
        if (size < 0) {
            std::cout << "ERROR : please input positive value" << std::endl;
        }
    } while(size < 0);

    for(unsigned int i(0); i < size; ++i) {
        neurons[i] = new Neuron(i);
    }
     */

    neuron1 = new Neuron(0);
    neuron2 = new Neuron(1);
    inCurrent = new Current;
    inCurrent1 = new Current;
}

void Simulation::TimeIncrement() {
    // Time incrementation
    ++time;
}

void Simulation::loop() {

    /* // Neuron update
    for(auto neuron : neurons) {
        neuron->update(getSimulationTime(), *inCurrent);
    }
     */

    // Neuron update
    neuron1->update(getSimulationTime(), *inCurrent, *neuron2);

    Neuron* neuronX = nullptr;

    neuron2->update(getSimulationTime(), *inCurrent1, *neuronX);

    // Increments time
    TimeIncrement();
}

void Simulation::run(double timeA, double timeB) {

    assert(timeA >= 0);
    assert(timeB >= timeA);

    while(time >= (timeA / TIME_H) and time <= (timeB / TIME_H)) {
        loop();
    }
}

double Simulation::timeMS() const {
    return (time * TIME_H);
}

unsigned long Simulation::getSimulationTime() const {
    return time;
}

std::vector<double> Simulation::getNeuronV(unsigned int ID) const {
    return (ID == 1) ? neuron1->getMembraneV() : neuron2->getMembraneV();
}
