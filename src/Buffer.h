//
// Created by Arnaud Dhaene on 09.10.17.
//

#ifndef BRUNEL_BUFFER_H
#define BRUNEL_BUFFER_H

#include <cmath>
#include <vector>
#include <cassert>

typedef std::pair<double, unsigned long> SpikeTransmission; // (J, time) = (Amplitude, time)

class Buffer {

public:

    /*!
     * @brief Constructor
     *
     */
    Buffer() = default;

    /*!
     * @brief Destructor
     *
     */
    ~Buffer() = default;

    /*!
     * @brief adds a Spike Transmission into buffer queue
     *
     */
     void addTransmission(SpikeTransmission);

    /*!
     * @brief adds a Spike Transmission into buffer queue
     *
     */
     void erase(unsigned long time);

    /*!
     * @brief returns the amplitude according to the time
     *
     * @note returns 0 if there is no attributes spike transmission
     */
    double amplitude(unsigned long);

private:

    std::vector<SpikeTransmission> queue;



};


#endif //BRUNEL_BUFFER_H
