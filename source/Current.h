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
    double getValue() const;

private:
    double value; // current value - in picoA

};


#endif //BRUNEL_CURRENT_H
