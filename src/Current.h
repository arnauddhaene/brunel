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
     * @brief Destructor
     *
     */
    ~Current() = default;

    //! Getters
    double getValue(unsigned long time) const; //! time in timesteps, not in ms
    double getStart() const;
    double getStop() const;

    //! Setters
    void setValue(double);
    void setStart(unsigned long);
    void setStop(unsigned long);
private:
    double value; //! current value - in picoA

    unsigned int ID; //! works the same way as neuron identification

    unsigned long start; //! start current time
    unsigned long stop; //! stop current time

};


#endif //BRUNEL_CURRENT_H
