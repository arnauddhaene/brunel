//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Neuron.h"
#include "Network.h"

double Neuron::c1 = exp( - C::TIME_H / C::TAU );
double Neuron::c2 = C::RESISTANCE * (1.0 - c1);

Neuron::Neuron( bool ty ) : mClock( 0 ), mPotential( C::V_RESET ), mExcitatory( ty ) {

    /// clearing vector structures
    mSpikeTimes.clear();
    mMembranePotentials.clear();
    mConnections.clear();

    assert(mSpikeTimes.empty());
    assert(mMembranePotentials.empty());
    assert(mConnections.empty());

    /// clearing array structure - initialisation at 0
    for ( double& bucket : mBuffer ) {
        bucket = 0;
    }

}

bool Neuron::update( bool membrane, bool spikes, double poisson, double current )
{
    bool spiking( false );

    // we must test if the potential is above the neuron's threshold
    if ( mPotential > C::V_THRESHOLD ) {

        // the neuron spikes
        if ( spikes ) {

            spike();

            assert(!mSpikeTimes.empty());
            assert(mSpikeTimes.back() == mClock);
        }

        spiking = true;

    }

    // first, we wish to know if the neuron is in a refractory state or not
    if ( !(!mSpikeTimes.empty() && C::REFRACTORY_TIME > (mClock - mSpikeTimes.back())) ) {

        // not refractory - potential is set according to the differential equation
        solveODE( current, poisson );

    }

    // the neuron's potential will be stored over time if needed
    if ( membrane ) {

        mMembranePotentials.push_back( mPotential );

    }

    assert(mClock == Network::clock);

    // we will update the neuron's local clock
    ++mClock;

    return spiking;
}


void Neuron::solveODE( double current, double poisson ) {

    assert(c1 != 0);
    assert(c2 != 0);

    /// we update the potential of neuron as it is not refractory
    mPotential = c1 * mPotential + c2 * current

                // connections from network
                + b_amplitude( mClock )

                // background noise
                + poisson;

    /// we remove transmission from buffer after transmission occurs (if it occurs)
    b_erase( mClock );
}

void Neuron::spike() {

    /// the spike is recorded in our records in the specified vector if needed
    mSpikeTimes.push_back( mClock );

    mPotential = C::V_RESET;
}

void Neuron::receiveSpike( unsigned long t, double transmission ) {
    mBuffer[(unsigned int) (t + C::DELAY) % (C::DELAY + 1)] += transmission;
}

std::vector<double> Neuron::getPotentials() const {
    return mMembranePotentials;
}

void Neuron::addConnection( unsigned int value ) {
    mConnections.push_back( value );
}

std::vector<unsigned long> Neuron::getSpikes() const {
    return mSpikeTimes;
}

const std::vector<unsigned int>& Neuron::getConnections() const {
    return mConnections;
}

void Neuron::b_erase( unsigned long time ) {
    mBuffer[(unsigned int) time % (C::DELAY + 1)] = 0;
}

double Neuron::b_amplitude( unsigned long time ) const {
    return mBuffer[(unsigned int) time % (C::DELAY + 1)];
}

bool Neuron::isExcitatory() const {
    return mExcitatory;
}