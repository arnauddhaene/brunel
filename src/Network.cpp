//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Network.h"
#include <ctime>

unsigned long Network::clock = 0;

Network::Network( unsigned int s, bool current, bool membrane, bool spikes, bool poisson, bool connections )
        : mCurrent( current ), mMembrane( membrane ), mSpikes( spikes ), mPoisson( poisson )

{
    for ( unsigned int i(0); i < s ; ++i ) { //! not using unsigned int for input purposes
        mNeurons.push_back(new Neuron(i < C::N_EXCITATORY)); //! 10 k excitatory, 2500 inhibitory

        /// here, i is the neuron's ID
        if ( current ) {
            mCurrents.push_back(new Current(0, i)); //! same for the currents
        }
    }

    /// We will now proceed with connection making if simulation is at max size
    if ( connections ) {
        generateConnections();
    }
}

Network::~Network() { reset(); }

void Network::loop() {

    assert(!mNeurons.empty());
    assert(mNeurons[0] != nullptr);


    /// Neuron update
    for ( size_t i(0); i < mNeurons.size(); ++i ) {

        //! Only 50 neurons will store spike times
        bool spike = mNeurons[i]->update(mMembrane, mSpikes,
                                                (mPoisson ? Network::getNoise() : 0),
                                                (mCurrent ? mCurrents[i]->getValue(clock) : 0));

        if ( spike ) {

            for ( auto connection : mNeurons[i]->getConnections() ) {

                /// if the neuron has connections, we will send the spike to these connections
                assert(!mNeurons[i]->getConnections().empty());

                mNeurons[connection]->receiveSpike( Network::clock, (mNeurons[i]->isExcitatory() ? C::J_AMP_EXCITATORY : C::J_AMP_INHIBITORY) );

            }

        }

    }

    /// Increments time
    ++Network::clock;

}

std::vector<Neuron*> Network::run( double endT )  {

    /// reinitialization in case of consecutive simulations of the same network
    Network::clock = 0;

    assert(Network::clock < endT * C::TIME_CONVERTER);

    while ( Network::clock < (endT * C::TIME_CONVERTER) ) {

        loop();

    }

    return mNeurons;
}

void Network::generateConnections() {

    /// random device
    static std::random_device device;
    static std::mt19937 gen( device() );

    /// excitatory connections
    static std::uniform_int_distribution<> dise( 0, (int) (C::E_RATIO * mNeurons.size()) - 1 );

    /// inhibitory connections
    static std::uniform_int_distribution<> disi( (int) (C::E_RATIO * mNeurons.size()), (int) mNeurons.size() - 1 );

    std::array<int, C::C_EXCITATORY> sources = {};
    std::array<int, C::C_INHIBITORY> sourcis = {};

    struct c_random_e {
        int operator()() { return dise(gen); }
    } getRandomConnectionE;

    struct c_random_i {
        int operator()() { return disi(gen); }
    } getRandomConnectionI;

    for (size_t i(0); i < mNeurons.size(); ++i) {

        /// placing connections in random arrays
        std::generate( sources.begin(), sources.end(), getRandomConnectionE );
        std::generate( sourcis.begin(), sourcis.end(), getRandomConnectionI );

        /// assign generated connection to attributed neurons
        for ( auto source : sources ) {
            mNeurons[source]->addConnection((unsigned int) i);
        }
        for (auto sourci : sourcis) {
            mNeurons[sourci]->addConnection((unsigned int) i);
        }

    }

}

std::vector<double> Network::getNeuronV( unsigned int ID ) const {
    return mNeurons[ID]->getPotentials();
}

void Network::setCurrent( double val, unsigned int id, unsigned long sta, unsigned long sto ) {
    delete mCurrents[id];
    mCurrents[id] = new Current(val, id, sta, sto);
}

double Network::getCurrent( unsigned int id, unsigned long time ) const {
    return mCurrents[id]->getValue(time);
}

Neuron* Network::getNeuron( unsigned int id ) const {
    return mNeurons[id];
}

void Network::reset() {

    //! deleting pointers for optimization of dynamic allocation

    for ( auto& neuron : mNeurons ) {
        delete neuron;
        neuron = nullptr;
    }

    if ( mCurrent ) {
        for(auto& current : mCurrents) {
            delete current;
            current = nullptr;
        }
    }

    Network::clock = 0;

}