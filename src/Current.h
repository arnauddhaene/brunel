//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_CURRENT_H
#define BRUNEL_CURRENT_H

#include <iostream>
#include "constants.h"
#include <cassert>

/*!
 * @class represents current associated to neuron or simulation
 *
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
    Current(double value, unsigned int id, unsigned long start, unsigned long stop);

    /*!
     * @brief Constructor overload for current without time restriction
     *
     * @param value in pA
     * @param id identification number of current
     */
    Current(double value, unsigned int id);

    /*!
     * @brief Destructor
     */
    ~Current() = default;

    /*!
     * @param time value of time in timesteps
     *
     * @note time in timesteps
     *
     * @return value of current at wanted time
     */
    double getValue(unsigned long time) const;

private:
    double value; //! current value - in pA

    unsigned int ID; //! current ID will correspond to neuron ID

    unsigned long start, stop; //! start and stop times in timesteps
};


#endif //BRUNEL_CURRENT_H
