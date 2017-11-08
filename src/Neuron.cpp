//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Neuron.h"
#include "Network.h"

double Neuron::c1 = exp(- C::TIME_H / C::TAU);
double Neuron::c2 = C::RESISTANCE * (1.0 - c1);

Neuron::Neuron(bool ty) : clock(0), potential(C::V_RESET), excitatory(ty) {

    /// clearing vector structures
    spikeTimes.clear();
    membranePotentials.clear();
    connections.clear();

    assert(spikeTimes.empty());
    assert(membranePotentials.empty());
    assert(connections.empty());

    /// clearing array structure - initialisation at 0
    for(double& bucket : buffer) {
        bucket = 0;
    }

}

bool Neuron::update(bool membrane, bool spikes, double poisson, double current)
{
    bool spiking(false);

    // we must test if the potential is above the neuron's threshold
    if (potential > C::V_THRESHOLD) {

        // the neuron spikes
        if (spikes) {

            spike();

            assert(!spikeTimes.empty());
            assert(spikeTimes.back() == clock);
        }

        spiking = true;

    }

    // first, we wish to know if the neuron is in a refractory state or not
    if (!(!spikeTimes.empty() && C::REFRACTORY_TIME > (clock - spikeTimes.back()))) {

        // not refractory - potential is set according to the differential equation
        solveODE(current, poisson);

    }

    // the neuron's potential will be stored over time if needed
    if (membrane) {

        membranePotentials.push_back(potential);

    }

    assert(clock == Network::clock);

    // we will update the neuron's local clock
    ++clock;

    return spiking;
}


void Neuron::solveODE(double current, double poisson) {

    assert(c1 != 0);
    assert(c2 != 0);

    /// we update the potential of neuron as it is not refractory
    potential = c1 * potential + c2 * current

                // connections from network
                + b_amplitude(clock)

                // background noise
                + poisson;

    /// we remove transmission from buffer after transmission occurs (if it occurs)
    b_erase(clock);
}

void Neuron::spike() {

    /// the spike is recorded in our records in the specified vector if needed
    spikeTimes.push_back(clock);

    potential = C::V_RESET;
}

void Neuron::receiveSpike(unsigned long t, double transmission) {
    buffer[(unsigned int) (t + C::DELAY) % (C::DELAY + 1)] += transmission;
}

std::vector<double> Neuron::getPotentials() const {
    return membranePotentials;
}

void Neuron::addConnection(unsigned int value) {
    connections.push_back(value);
}

std::vector<unsigned long> Neuron::getSpikes() const {
    return spikeTimes;
}

const std::vector<unsigned int>& Neuron::getConnections() const {
    return connections;
}

void Neuron::b_erase(unsigned long time) {
    buffer[(unsigned int) time % (C::DELAY + 1)] = 0;
}

double Neuron::b_amplitude(unsigned long time) const {
    return buffer[(unsigned int) time % (C::DELAY + 1)];
}

bool Neuron::isExcitatory() const {
    return excitatory;
}