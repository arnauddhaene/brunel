//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"

Simulation::Simulation(unsigned int size) : time(0) {

    for( int i(0); i < size; ++i) { //! not using unsigned int for input purposes
        neurons.push_back(new Neuron(i)); //! here, i is the neuron's ID
        currents.push_back(new Current(0, i, 0, 0)); //! same for the currents
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

    while(time >= (timeA * TIME_CONVERTER) and time <= (timeB * TIME_CONVERTER)) {
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

void Simulation::setCurrent(double val, unsigned int id, unsigned long sta, unsigned long sto) {
    delete currents[id];
    currents[id] = new Current(val, id, sta, sto);
}

double Simulation::getCurrent(unsigned int id, unsigned long time) const {
    return currents[id]->getValue(time);
}

Neuron* Simulation::getNeuron(unsigned int id) const {
    return neurons[id];
}