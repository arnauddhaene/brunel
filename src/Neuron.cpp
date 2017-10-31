//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Neuron.h"
#include "Network.h"

double Neuron::c1 = exp(- C::TIME_H / C::TAU);
double Neuron::c2 = C::RESISTANCE * (1.0 - c1);

Neuron::Neuron(unsigned int id, bool ty) : clock(0), potential(C::V_RESET), refractory(false), excitatory(ty), ID(id) {

    spikeTimes.clear();

    membranePotentials.clear();

    buffer = new Buffer;

}

void Neuron::update(std::vector<Current*>* allcurrents, std::vector<Neuron*>* allneurons,
                    bool membrane, bool spikes, bool poisson, bool current)
{

    /// first, we wish to know if the neuron is already in a refractory state or not
    if(refractory) {

        /// if it is in refractory mode, we will update it accordingly
        updateRefractory();

    } else {

        /// here, we set the new potential according to the differential equation from Brunel's paper
        solveODE((current ? (*allcurrents)[ID] : new Current(0, 0, 0, 0)), poisson);

        /// we must now test if this value is above the neuron's threshold
        if(potential > C::V_THRESHOLD) {

            /// the neuron spikes
            spike(allneurons, spikes);

        }
        /// in the case that the new potential is below the threshold, we simply continue the simulation
    }

    /// the neuron's potential will be stored over time if needed
    if(membrane) {

        storePotential();

    }

    /// we will update the neuron's local clock
    ++clock;
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

void Neuron::solveODE(Current* current, bool poisson) {

    /// we update the potential of neuron as it is not refractory
    potential = c1 * potential + c2 * current->getValue(clock)

                // connections from network
                + getBuffer()->amplitude(clock)

                // background noise
                + (poisson ? Network::getNoise(): 0);

    /// we remove transmission from buffer after transmission occurs
    getBuffer()->erase(clock);
}

void Neuron::spike(std::vector<Neuron*>* allneurons, bool spikes) {

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

    assert(!allneurons->empty());


    /// we now wish to send spike to connecting neurons
    for(unsigned int connection : connections) {

        assert(!connections.empty());

        /// if the neuron has connections, we will send the spike to these connections
        assert((*allneurons)[connection] != nullptr);

        (*allneurons)[connection]->receiveSpike(excitatory);

    }
}

void Neuron::storePotential() {
    membranePotentials.push_back(potential);
}

void Neuron::receiveSpike(bool excitatory) {
    buffer->addTransmission(clock, excitatory);
}

std::vector<double> Neuron::getPotentials() const {
    return membranePotentials;
}

Buffer* Neuron::getBuffer() const {
    return buffer;
}

void Neuron::addConnection(unsigned int value) {
    connections.push_back(value);
}

std::vector<unsigned long> Neuron::getSpikes() const {
    return spikeTimes;
}