//
// Created by Arnaud Dhaene on 09.10.17.
//

#ifndef BRUNEL_BUFFER_H
#define BRUNEL_BUFFER_H

#include <cmath>
#include <vector>
#include <cassert>
#include "constants.h"

/*!
 * @class represents a neuron's ring buffer
 *
 */
class Buffer {

public:
    /*!
     * @brief Constructor
     *
     * @note queue is filled with 0 value
     */
    Buffer();

    /*!
     * @brief Destructor
     *
     */
    ~Buffer() = default;

    /*!
     * @brief adds a Spike Transmission into buffer queue
     *
     * @param time corresponding to appropriate spike transmission
     */
    void addTransmission(unsigned long time);

    /*!
     * @brief adds a Spike Transmission into buffer queue
     *
     * @param current time
     */
    void erase(unsigned long time);

    /*!
     * @brief returns the amplitude according to the time
     *
     * @param time simulation time
     * @param excitatory type of neuron
     *
     * @note returns 0 if there is no attributed spike transmission
     *
     * @return amplitude of transmitted spike in mV
     */
    double amplitude(unsigned long time, bool excitatory);

    /*!
     * @brief returns index of buffer in which to write
     *
     * @param current time
     *
     * @return index corresponding to given time
     */
    unsigned int index(unsigned long time);

    /*!
    * @brief get buffer size
     *
    * @return buffer size
    */
    unsigned long size() const;

private:
    /// We will stores ints as scalar multipliers of J_AMP
    std::vector<unsigned int> bufqueue;

};


#endif //BRUNEL_BUFFER_H
