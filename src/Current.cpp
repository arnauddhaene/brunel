//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Current.h"

Current::Current() {

    // Current value
    std::cout << "Input external current value (picoA) :" << std::endl;
    do {
        std::cin >> value;
        if (value < 0) {
            std::cout << "ERROR : please input positive value" << std::endl;
        }
    } while(value < 0);

    // Start value
    std::cout << "from time (in ms) :" << std::endl;

    std::cin  >> start;

    start /= TIME_H; // time was entered in ms

    // Stop value
    std::cout << "until time (in ms) :" << std::endl;
    do {
        std::cin >> stop;
        if (stop <= start * TIME_H) {
            std::cout << "ERROR : stop time must be later than start time" << std::endl;
        }
    } while(stop <= start * TIME_H);

    stop /= TIME_H; // time was entered in ms
}

double Current::getValue(unsigned long time) const {
   return (time >= start && time <= stop) ? value : 0;
}

double Current::getStart() const {
    return start;
}

double Current::getStop() const {
    return stop;
}