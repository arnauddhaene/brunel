//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Neuron.h"
#include "Network.h"
#include <iostream>

double Neuron::c1 = exp(- C::TIME_H / C::TAU);
double Neuron::c2 = C::RESISTANCE * (1.0 - c1);

Neuron::Neuron(bool ty) : clock(0), potential(C::V_RESET), refractory(false), excitatory(ty) {

    spikeTimes.clear();

    membranePotentials.clear();

    connections.clear();

    /// Making sure all values start at 0 - clearing buffer
    for(auto& bucket : buffer) {
        bucket = 0;
    }

}

bool Neuron::update(bool membrane, bool spikes, bool poisson, double curr)
{
    bool spiking(false);

    /// first, we wish to know if the neuron is already in a refractory state or not
    if(refractory) {

        /// if it is in refractory mode, we will update it accordingly
        updateRefractory();

    } else {

        /// here, we set the new potential according to the differential equation from Brunel's paper
        solveODE(curr, (poisson ? Network::getNoise() : 0));

        /// we must now test if this value is above the neuron's threshold
        if(potential > C::V_THRESHOLD) {

            /// the neuron spikes
            spike(spikes);

            spiking = true;

        }
        /// in the case that the new potential is below the threshold, we simply continue the simulation
    }

    /// the neuron's potential will be stored over time if needed
    if(membrane) {

        membranePotentials.push_back(potential);

    }

    /// we will update the neuron's local clock
    ++clock;

    return spiking;
}

void Neuron::updateRefractory() {

    /// if the neuron is refractory, we set the potential to V_RESET which will cause the 'spike'
    potential = C::V_RESET;

    /// if there is remaining refractory time, we decrease it by one timestep
    if(reftime > 0) {

        --reftime;

    } else {

        //! otherwise, we change the state to inactive (non refractory)
        refractory = false;

        reftime = 0;
    }
}

void Neuron::solveODE(double current, double poisson) {

    /// we update the potential of neuron as it is not refractory
    potential = c1 * potential + c2 * current

                // connections from network
                + b_amplitude(clock)

                // background noise
                + poisson;

    /// we remove transmission from buffer after transmission occurs (if it occurs)
    b_erase(clock);
}

void Neuron::spike(bool spikes) {

    /// the potential will spike once it is above the threshold
    potential = C::V_THRESHOLD;

    /// the spike is recorded in our records in the specified vector if needed
    if(spikes) {

        spikeTimes.push_back(clock);

        assert(!spikeTimes.empty());

    }

    /// we must now set the neuron in refractory mode
    refractory = true;

    /// finally, the refractory time is set in order to let the neuron "do it's time"
    reftime = C::REFRACTORY_TIME;

}

void Neuron::receiveSpike(unsigned long t, double transmission) {
    b_addTransmission(t, transmission);
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

void Neuron::b_addTransmission(unsigned long time, double transmission) {
    buffer[b_index(time + C::DELAY)] += transmission;
}

void Neuron::b_erase(unsigned long time) {
    buffer[b_index(time)] = 0;
}

double Neuron::b_amplitude(unsigned long time) const {
    return buffer[b_index(time)];
}

unsigned int Neuron::b_index(unsigned long time) const {
    return (unsigned int)(time % (C::DELAY + 1));
}

bool Neuron::isExcitatory() const {
    return excitatory;
}