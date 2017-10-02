//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_CURRENT_H
#define BRUNEL_CURRENT_H

#include <iostream>


class Current {
public:
    Current();
    ~Current() = default;

    // getters
    double getValue() const;

private:
    double value;

};


#endif //BRUNEL_CURRENT_H
