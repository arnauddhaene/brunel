//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Network.h"
#include <ctime>

Network::Network(unsigned int s, bool current_, bool membrane_, bool spikes_, bool poisson_, bool connections_)
        : net_clock(0), current(current_), membrane(membrane_), spikes(spikes_), poisson(poisson_)

{
    clock_t t1, t2;

    t1 = clock();

    for(unsigned int i(0); i < s ; ++i) { //! not using unsigned int for input purposes
        neurons.push_back(new Neuron(i < C::N_EXCITATORY)); //! 10 k excitatory, 2500 inhibitory

        /// here, i is the neuron's ID
        if(current_) {
            currents.push_back(new Current(0, i)); //! same for the currents
        }
    }

    /// We will now proceed with connection making if simulation is at max size
    if(connections_) {

        generateConnections();
    }

    t2 = clock();

    std::cout << "Network creation time : " << ((float) t2 - (float) t1) / CLOCKS_PER_SEC << " seconds" << '\n';
}

Network::~Network() {
    reset();
}

void Network::loop() {

    /// Neuron update
    for(size_t i(0); i < neurons.size(); ++i) {

        //! Only 50 neurons will store spike times
        bool spike = neurons[i]->update(membrane, spikes, poisson, (current ? currents[i]->getValue(net_clock) : 0));

        if(spike) {

            for(auto bullseye : neurons[i]->getConnections()) {

                /// if the neuron has connections, we will send the spike to these connections
                assert(!neurons[i]->getConnections().empty());

                neurons[bullseye]->receiveSpike(net_clock, (neurons[i]->isExcitatory() ? C::J_AMP_EXCITATORY : C::J_AMP_INHIBITORY));

            }

        }

    }

    /// Increments time
    ++net_clock;
}

std::vector<Neuron*> Network::run(double endT)  {

    assert(endT >= 0);

    // int STEPPER(0);

    clock_t t1, t2;

    t1 = clock();

    while(net_clock<= (endT * C::TIME_CONVERTER)) {

        loop();

    }

    t2 = clock();

    std::cout << "Network runtime : " << ((float) t2 - (float) t1) / CLOCKS_PER_SEC << " seconds" << '\n';

    return neurons;
}

void Network::generateConnections() {

    /*
    /// random device
    static std::random_device device;
    static std::mt19937 gen(device());

    /// excitatory connections
    static std::uniform_int_distribution<> dise(0, (int)(C::E_I_RATI0 * neurons.size()) - 1);

    /// inhibitory connections
    static std::uniform_int_distribution<> disi((int)(C::E_I_RATI0 * neurons.size()), (int)neurons.size() - 1);

    for(size_t target(0); target < neurons.size(); ++target) {

        std::array<int, C::C_TOTAL> sources = {};

        for(size_t i(0); i < C::C_TOTAL; ++i) {

            auto source = ((i <  C::C_EXCITATORY) ? dise(gen) : disi(gen));
            sources[i] = source;

        }

        for(auto source : sources) {
            neurons[source]->addConnection((unsigned int) target);
        }

    }
    */


    /// random device
    static std::random_device device;
    static std::mt19937 gen(device());

    /// excitatory connections
    static std::uniform_int_distribution<> dise(0, (int) (C::E_I_RATI0 * neurons.size()) - 1);

    /// inhibitory connections
    static std::uniform_int_distribution<> disi((int) (C::E_I_RATI0 * neurons.size()), (int) neurons.size() - 1);

    std::array<int, C::C_EXCITATORY> sources = {};
    std::array<int, C::C_INHIBITORY> sourcis = {};

    struct c_random_e {
        int operator()() { return dise(gen); }
    } getRandomConnectionE;

    struct c_random_i {
        int operator()() { return disi(gen); }
    } getRandomConnectionI;

    for(size_t i(0); i < neurons.size(); ++i) {

        std::generate(sources.begin(), sources.end(), getRandomConnectionE);
        std::generate(sourcis.begin(), sources.end(), getRandomConnectionI);

        /// assign generated connection to attributed neurons
        for (auto source : sources) {
            neurons[source]->addConnection((unsigned int) i);
        }
        for (auto sourci : sourcis) {
            neurons[sourci]->addConnection((unsigned int) i);
        }

    }

}


std::vector<double> Network::getNeuronV(unsigned int ID) const {
    return neurons[ID]->getPotentials();
}

void Network::setCurrent(double val, unsigned int id, unsigned long sta, unsigned long sto) {
    delete currents[id];
    currents[id] = new Current(val, id, sta, sto);
}

double Network::getCurrent(unsigned int id, unsigned long time) const {
    return currents[id]->getValue(time);
}

Neuron* Network::getNeuron(unsigned int id) const {
    return neurons[id];
}

void Network::reset() {

    for(auto& neuron : neurons) {
        delete neuron;
        neuron = nullptr;
    }

    if(current) {
        for(auto& current : currents) {
            delete current;
            current = nullptr;
        }
    }

    net_clock = 0;

}