//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"

Simulation::Simulation(unsigned int size) : time(0) {

    for(unsigned int i(0); i < size; ++i) { //! not using unsigned int for input purposes
        neurons.push_back(new Neuron(i, (i < 10000))); //! 10 k excitatory, 2500 inhibitory
        /// here, i is the neuron's ID
        currents.push_back(new Current(0, i)); //! same for the currents
    }

    /// We will now proceed with connection making if simulation is at max size
    if(size == C::SIMULATION_SIZE) {
        generateConnections(size);
    }
}

void Simulation::TimeIncrement() {
    /// Time incrementation
    ++time;
}

void Simulation::loop() {

    /// Neuron update
    for(unsigned int i(0); i < neurons.size(); ++i) {

        neurons[i]->update(getSimulationTime(), &currents, &neurons);

    }

    /// Increments time
    TimeIncrement();
}

std::vector<Neuron*>* Simulation::run(double timeA, double timeB) {

    assert(timeA >= 0);
    assert(timeB >= timeA);

    while(time >= (timeA * C::TIME_CONVERTER) and time <= (timeB * C::TIME_CONVERTER)) {
        loop();
    }

    return &neurons;
}

double Simulation::timeMS() const {
    return (time * C::TIME_H);
}

void Simulation::generateConnections(unsigned int size) {

    /// random generators
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<> dis_e(0, 9999); //! these IDs correspond to excitatory neurons
    std::uniform_int_distribution<> dis_i(10000, 12490); //! these IDs correspond to inhibitory neurons

    /// We then randomly input 1250 neuron connection into connections vector
    for(unsigned int i(0); i < neurons.size(); ++i) {
        for(unsigned int j(0); j < (C::C_EXCITATORY + C::C_INHIBITORY); ++j) {
            neurons[(j < C::C_EXCITATORY) ? (unsigned int)dis_e(gen) : (unsigned int)dis_i(gen)]->addConnection(i);
        }
    }
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