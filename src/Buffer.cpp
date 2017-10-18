//
// Created by Arnaud Dhaene on 09.10.17.
//

#include "Buffer.h"


Buffer::Buffer() {
    for(unsigned int i(0) ; i < DELAY + 1; ++i) {
        queue.push_back(0);
    }
}

void Buffer::addTransmission(unsigned long time) {
    ++queue[index(time + DELAY)];
}

void Buffer::erase(unsigned long time) {
    queue[index(time)] = 0;
}

double Buffer::amplitude(unsigned long time) {
    return J_AMP * queue[index(time)];
}

unsigned int Buffer::index(unsigned long time) {
    return time % (DELAY + 1);
}

unsigned int Buffer::size() const {
    return queue.size();
}