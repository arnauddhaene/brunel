//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_CURRENT_H
#define BRUNEL_CURRENT_H

#include <iostream>


class Current {
public:
    /*!
     * @brief Constructor
     *
     * @note asks user to input current value when initialized
     */
    Current();

    /*!
     * @brief Destructor
     *
     */
    ~Current() = default;

    // Getters
    double getValue(double time) const;
    double getStart() const;
    double getStop() const;

private:
    double value; // current value - in picoA

    unsigned long start; // start current time - in ms
    unsigned long stop; // stop current time - in ms

};


#endif //BRUNEL_CURRENT_H
