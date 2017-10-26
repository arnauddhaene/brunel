//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Simulation.h"

Simulation::Simulation(unsigned int s) : time(0) {

    for(unsigned int i(0); i < s; ++i) { //! not using unsigned int for input purposes
        neurons.push_back(new Neuron(i, (i < 9999))); //! 10 k excitatory, 2500 inhibitory
        /// here, i is the neuron's ID
        currents.push_back(new Current(0, i)); //! same for the currents
    }

    /// We will now proceed with connection making if simulation is at max size
    generateConnections();
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

    int STEPPER(0);

    while(time >= (timeA * C::TIME_CONVERTER) and time <= (timeB * C::TIME_CONVERTER)) {
        loop();

        //if(time % (int)((timeB - timeA) * C::TIME_CONVERTER / 20) == 0) {
            ++STEPPER;
            std::cout << "Timestep " << STEPPER << std::endl;
        //}
    }

    return &neurons;
}

double Simulation::timeMS() const {
    return (time * C::TIME_H);
}

void Simulation::generateConnections() {

    //! note : 0.8 = 100/125 -> ratio of excitatory vs. inhibitory
    int numbE = (8 * (int)neurons.size()) / 10;

    //! for the excitatory connections
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<> dis(0, numbE - 1);

    //! for the inhibitory connections
    std::random_device device1;
    std::mt19937 gen1(device1());
    std::uniform_int_distribution<> dis1(numbE, (int)neurons.size() - 1);

    /// We then randomly input 1250 neuron connection into connections vector
    for(unsigned int i(0); i < neurons.size(); ++i) {
        for(unsigned int j(0); j < (C::C_EXCITATORY + C::C_INHIBITORY); ++j) {
            // neurons[(j < C::C_EXCITATORY) ? (unsigned int)dis_e(gen) : (unsigned int)dis_i(gen)]->addConnection(i);
            if(j < C::C_EXCITATORY) {
                neurons[dis(gen)]->addConnection(i);
            } else {
                neurons[dis1(gen1)]->addConnection(i);
            }
        }
    }

    //! generation of connections done
    std::cout << "Connection generation finished." << std::endl;

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