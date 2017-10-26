//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Neuron.h"


Neuron::Neuron(unsigned int id, bool ty) : membraneV(C::V_RESET), refractory(false), ID(id), buffer(0), type(ty) {

    membranePotentials.push_back(getPotential());

    buffer = new Buffer;

    connections.push_back(ID + 1);
}

void Neuron::update(unsigned long time, std::vector<Current*>* allcurrents, std::vector<Neuron*>* allneurons) {

    /// first, we wish to know if the neuron is already in a refractory state or not
    if(isRefractory()) {

        /// if it is in refractory mode, we will update it accordingly
        updateRefractory();

    } else {

        /// here, we set the new potential according to the differential equation from Brunel's paper
        solveODE(time, (*allcurrents)[ID]);

        /// we must now test if this value is above the neuron's threshold
        if(getPotential() > C::V_THRESHOLD) {

            /// the neuron spikes
            spike(time, allneurons);

        }
        /// in the case that the new potential is below the threshold, we simply continue the simulation
    }

    /// in any case, the neuron's potential will be stored over time
    storeV();

    /// we will update the neuron's local clock
    ClockIncrement();
}

void Neuron::updateRefractory() {

    /// if the neuron is refractory, we set the potential to V_RESET
    /// this will cause the 'spike'
    setPotential(C::V_RESET);
    /// if there is remaining refractory time, we decrease it by one timestep
    if(getRefTime() > 0) {
        setRefTime(getRefTime() - 1);
    } else {
        //! otherwise, we change the state to inactive (non refractory)
        setRefractory(false);
        setRefTime(0);
    }
}

void Neuron::solveODE(unsigned long time, Current* inC) {

    /// Creates poisson distribution
    std::random_device pd;
    std::mt19937 gen(pd());
    std::poisson_distribution<> poisson(C::V_EXT * C::C_EXCITATORY * C::TIME_H * C::J_AMP_EXCITATORY);

    /// we update the potential of neuron as it is not refractory
    setPotential(
            (exp(-(C::TIME_H/C::TAU)) * getPotential()
             + C::RESISTANCE * (1 - exp(-(C::TIME_H/C::TAU))) * inC->getValue(time))
             + getBuffer()->amplitude(time, isExcitatory())
             + poisson(gen)
    );

    /// we remove transmission from buffer after transmission occurs
    getBuffer()->erase(time);

    assert(getBuffer()->amplitude(time, isExcitatory()) >= 0);
}

void Neuron::spike(unsigned long time, std::vector<Neuron*>* allneurons) {

    /// the potential will spike once it is above the threshold
    setPotential(C::V_THRESHOLD);
    /// the spike is recorded in our records in the specified vector
    spikeTimes.push_back(time);

    assert(!spikeTimes.empty());

    /// we must now set the neuron in refractory mode
    setRefractory(true);
    /// finally, the refractory time is set in order to let the neuron "do it's time"
    setRefTime(C::REFRACTORY_TIME);

    /// we now wish to send spike to connecting neurons
    for(unsigned int i(0); i < allneurons->size(); ++i) {

        for(unsigned int j(0); j < connections.size(); ++j) {
            /// if the neuron has connections, we will send the spike to these connections

            assert(!connections.empty());

            /// If neuron is connected, he will receive spike
            if((*allneurons)[i] != nullptr && connections[j]  == i) {
                (*allneurons)[i]->receiveSpike(time);
            }
        }
    }
}

void Neuron::storeV() {
    membranePotentials.push_back(getPotential());
}

void Neuron::ClockIncrement() {
    ++clock;
}

void Neuron::receiveSpike(unsigned long time) {
    buffer->addTransmission(time);
}

bool Neuron::isRefractory() const {
    return refractory;
}

double Neuron::getPotential() const {
    return membraneV;
}

unsigned long Neuron::getRefTime() const {
    return reftime;
}

int Neuron::getSpikesNumber() const {
    return (int)spikeTimes.size();
}

std::vector<double> Neuron::getMembraneV() const {
    return membranePotentials;
}

double Neuron::getMembraneV(unsigned int i) const {
    return membranePotentials[i];
}

Buffer* Neuron::getBuffer() const {
    return buffer;
}

bool Neuron::isExcitatory() const {
    return type;
}

void Neuron::setRefractory(bool s) {
    refractory = s;
}

void Neuron::setPotential(double v) {
    membraneV = v;
}

void Neuron::setRefTime(unsigned long r) {
    reftime = r;
}

void Neuron::addConnection(unsigned int value) {
    connections.push_back(value);
}

std::vector<unsigned long> Neuron::getSpikes() const {
    return spikeTimes;
}