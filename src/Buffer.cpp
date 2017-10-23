//
// Created by Arnaud Dhaene on 09.10.17.
//

#include "Buffer.h"


Buffer::Buffer() {
    for(unsigned int i(0) ; i < C::DELAY + 1; ++i) {
        bufqueue.push_back(0);
    }
}

void Buffer::addTransmission(unsigned long time) {
    ++bufqueue[index(time + C::DELAY)];
}

void Buffer::erase(unsigned long time) {
    bufqueue[index(time)] = 0;
}

double Buffer::amplitude(unsigned long time, bool excitatory) {
    return (excitatory ? C::J_AMP_EXCITATORY : C::J_AMP_INHIBITORY) * bufqueue[index(time)];
}

unsigned int Buffer::index(unsigned long time) {
    return (unsigned int)(time % (C::DELAY + 1));
}

unsigned long Buffer::size() const {
    return bufqueue.size();
}