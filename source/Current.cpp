//
// Created by Arnaud Dhaene on 02.10.17.
//

#include "Current.h"

Current::Current() {
    std::cout << "Input external current value (picoA) :" << std::endl;
    do {
        std::cin >> value;
        if (value <= 0) {
            std::cout << "ERROR : please input positive value" << std::endl;
        }
    } while(value <= 0);
}

double Current::getValue() const {
    return value;
}