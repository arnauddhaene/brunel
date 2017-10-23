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
     * @param value, ID, start time, stop time in ms
     */
    Current(double, unsigned int, unsigned long, unsigned long);

    /*!
     * @brief Constructor overload for unlimited constant current
     *
     * @param value, ID
     */
    Current(double, unsigned int);

    /*!
     * @brief Destructor
     *
     */
    ~Current() = default;

    /*!
     *
     * @param time value of time in timesteps
     * @return value of current at wanted time
     */
    double getValue(unsigned long time) const; //! time in timesteps, not in ms

    /*!
     * @brief gets Start time
     * @return start time of current value
     */
    double getStart() const;

    /*!
     * @brief gets Stop time
     * @return stop time of current value
     */
    double getStop() const;

    /*!
     *
     * @brief sets value in picoAmpers
     * @param val wanted value of current
     */
    void setValue(double val);

    /*!
     * @brief sets start time
     * @param sta  time in timesteps
     */
    void setStart(unsigned long sta);

    /*!
     * @brief sets stop time
     * @param sto time in timesteps
     */
    void setStop(unsigned long sto);

private:
    double value; //! current value - in picoA

    unsigned int ID; //! works the same way as neuron identification

    unsigned long start; //! start current time
    unsigned long stop; //! stop current time

};


#endif //BRUNEL_CURRENT_H
