//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_CURRENT_H
#define BRUNEL_CURRENT_H

#include <iostream>


class Current {
public:
    Current();
    ~Current();

    // getters
    double getValue(double time, double timeA, double timeB) const;

private:
    double value;

};


#endif //BRUNEL_CURRENT_H
