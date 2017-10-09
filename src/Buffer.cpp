//
// Created by Arnaud Dhaene on 09.10.17.
//

#include "Buffer.h"

void Buffer::addTransmission(SpikeTransmission st) {
    queue.push_back(st);
}

void Buffer::erase(unsigned long time) {
    for(unsigned int i(0); i < queue.size(); ++i) {
        if(std::get<1>(queue[i]) < time) {
            queue.erase(std::vector<SpikeTransmission>::iterator(queue.begin() + i));
        }
    }

}

double Buffer::amplitude(unsigned long time) {

    double amplitude(0);

    for(unsigned int i(0); i < queue.size(); ++i) {
        if(pow(1, -9) > (std::abs((float)(std::get<1>(queue[i]) - time)))) {
            amplitude += std::get<0>(queue[i]);
        }
    }

    return amplitude;
}