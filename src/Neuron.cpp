//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Neuron.h"


Neuron::Neuron(unsigned int id) : membraneV(V_RESET), refractory(false), ID(id), buffer(0) {

    membranePotentials.push_back(getPotential());

    buffer = new Buffer;

    connections.push_back(ID + 1);
}

void Neuron::update(unsigned long time, std::vector<Current*>* allcurrents, std::vector<Neuron*>* allneurons) {

    //! first, we wish to know if the neuron is already in a refractory state or not
    if(getRefractory()) {

        //! if it is in refractory mode, we will update it accordingly
        updateRefractory();

    } else {

        //! here, we set the new potential according to the differential equation from Brunel's paper
        solveODE(time, (*allcurrents)[ID]);

        //! we must now test if this value is above the neuron's threshold
        if(getPotential() > V_THRESHOLD) {

            //! the neuron spikes
            spike(time, allneurons);

        }
        //! in the case that the new potential is below the threshold, we simply continue the simulation
    }

    //! in any case, the neuron's potential will be stored over time
    storeV();

    //! we will update the neuron's local clock
    ClockIncrement();
}

void Neuron::updateRefractory() {

    //! if the neuron is refractory, we set the potential to V_RESET
    //! this will cause the 'spike'
    setPotential(V_RESET);
    //! if there is remaining refractory time, we decrease it by one timestep
    if(getRefTime() > 0) {
        setRefTime(getRefTime() - 1);
    } else {
        //! otherwise, we change the state to inactive (non refractory)
        setRefractory(false);
        setRefTime(0);
    }
}

void Neuron::solveODE(unsigned long time, Current* inC) {

    //! we update the potential of neuron as it is not refractory
    setPotential(
            (exp(-(TIME_H/TAU)) * getPotential()
             + RESISTANCE * (1 - exp(-(TIME_H/TAU))) * inC->getValue(time))
             + buffer->amplitude(time)
    );

    //! we remove transmission from buffer after transmission occurs
    buffer->erase(time);

    assert(buffer->amplitude(time) >= 0);
}

void Neuron::spike(unsigned long time, std::vector<Neuron*>* allneurons) {

    //! the potential will spike once it is above the threshold
    setPotential(V_THRESHOLD);
    //! the spike is recorded in our records in the specified vector
    spikeTimes.push_back(time);

    assert(spikeTimes.size() > 0);

    //! we must now set the neuron in refractory mode
    setRefractory(true);
    //! finally, the refractory time is set in order to let the neuron "do it's time"
    setRefTime(REFRACTORY_TIME);

    //! we now wish to send spike to connecting neurons
    for(unsigned int i(0); i < allneurons->size(); ++i) {

        for(unsigned int j(0); j < connections.size(); ++j) {
            //! if the neuron has connections, we will send the spike to these connections

            assert(!connections.empty());

            if((*allneurons)[i] != nullptr && i == connections[j] ) {

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

//! Getters
bool Neuron::getRefractory() const {
    return refractory;
}

double Neuron::getPotential() const {
    return membraneV;
}

double Neuron::getRefTime() const {
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

//! Setters
void Neuron::setRefractory(bool s) {
    refractory = s;
}

void Neuron::setPotential(double v) {
    membraneV = v;
}

void Neuron::setRefTime(double r) {
    reftime = r;
}

Buffer* Neuron::getBuffer() const {
    return buffer;
}