//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Current.h"

Current::Current() {
    std::cout << "Input external current value (picoA) :" << std::endl;
    do {
        std::cin >> value;
        if (value < 0) {
            std::cout << "ERROR : please input positive value" << std::endl;
        }
    } while(value < 0);

    std::cout << "from time (in ms) :" << std::endl;
    do {
        std::cin >> start;
        if (start < 0) {
            std::cout << "ERROR : please input positive value for start time" << std::endl;
        }
    } while(start < 0);

    std::cout << "until time (in ms) :" << std::endl;
    do {
        std::cin >> stop;
        if (stop <= start) {
            std::cout << "ERROR : stop time must be later than start time" << std::endl;
        }
    } while(stop <= start);
}

double Current::getValue(double time) const {
   return (time >= start && time <= stop) ? value : 0;
}

double Current::getStart() const {
    return start;
}

double Current::getStop() const {
    return stop;
}