//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_CURRENT_H
#define BRUNEL_CURRENT_H

#include <iostream>
#include "constants.h"
#include <cassert>


class Current {
public:
    /*!
     * @brief Constructor
     *
     * @note asks user to input current value when initialized
     * @param is current ID attributed at creation
     */
    Current(unsigned int);

    /*!
     * @brief Destructor
     *
     */
    ~Current() = default;

    //! Getters
    double getValue(unsigned long time) const;
    double getStart() const;
    double getStop() const;

private:
    double value; //! current value - in picoA

    unsigned int ID; //! works the same way as neuron identification

    unsigned long start; //! start current time - in ms
    unsigned long stop; //! stop current time - in ms

};


#endif //BRUNEL_CURRENT_H
