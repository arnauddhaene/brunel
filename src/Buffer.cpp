//
// Created by Arnaud Dhaene on 09.10.17.
//

#include "Buffer.h"

Buffer::Buffer() {

    /// Making sure all values start at 0 - clearing buffer
    for(auto& pot : pending) {
        pot = 0;
    }

}

void Buffer::addTransmission(unsigned long time, bool excitatory) {
    pending[index(time + C::DELAY)] += (excitatory ? C::J_AMP_EXCITATORY : C::J_AMP_INHIBITORY);
}

void Buffer::erase(unsigned long time) {
    pending[index(time)] = 0;
}

double Buffer::amplitude(unsigned long time) {
    return pending[index(time)];
}

unsigned int Buffer::index(unsigned long time) {
    return (unsigned int)(time % (C::DELAY + 1));
}

unsigned long Buffer::size() const {
    return pending.size();
}