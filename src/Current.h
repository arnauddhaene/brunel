//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_CURRENT_H
#define BRUNEL_CURRENT_H

#include <iostream>
#include "constants.h"
#include <cassert>

/*!
 * @brief represents current associated to neuron
 *
 * could be useful later on for specific simulations
 */
class Current {

public:
    /*!
     * @brief Constructor
     *
     * @param value
     * @param id identification
     * @param start time in ms
     * @param stop time in ms
     *
     * @note times will be converted during construction
     */
    Current(double value, unsigned int id, unsigned long start = 0, unsigned long stop = (unsigned long) 1e9);

    /*!
     * @brief Destructor
     */
    ~Current() = default;

    /*!
     * @param time value of time in timesteps
     *
     * @return value of current at wanted time
     */
    double getValue(unsigned long time) const;

private:
    double value; //! current value - in pA

    unsigned int ID; //! current identification number - setting specific currents for specific neurons

    unsigned long start, stop; //! start and stop times in timesteps
};


#endif //BRUNEL_CURRENT_H
