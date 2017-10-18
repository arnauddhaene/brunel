//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_CONSTANTS_H
#define BRUNEL_CONSTANTS_H

#include <cmath>

//! Simulation specific constants
constexpr double TIME_H = 0.1;                      //! Time increment value - in ms
constexpr unsigned long TIME_CONVERTER = 10;        //! Instead of dividing by TIME_H, we multiply by this

//! Neuron specific constants
constexpr double TAU = 20.0;                        //! Neuron Tau time constant : tau = RC - in ms
constexpr double CAPACITOR_C = 1.0;                 //! Neuron Capacitor value - in pF
constexpr double RESISTANCE = TAU/CAPACITOR_C;      //! Neuron resistance value - in ms/pF
constexpr double V_THRESHOLD = 20.0;                //! Neuron threshold value - in mV
constexpr double V_RESET = 0.0;                     //! Neuron inactive potential - in mV
constexpr double REFRACTORY_TIME = 2.0 * TIME_CONVERTER;
//constexpr double REFRACTORY_TIME = static_cast<unsigned long>(std::ceil(2.0 / TIME_H));;    //! Neuron refractory period - in timesteps

//! Connection constants
constexpr double J_AMP = 0.1;                        //! Connection spike amplitude in mV
constexpr unsigned long DELAY = 1.5 * TIME_CONVERTER;
//constexpr unsigned long DELAY = static_cast<unsigned long>(std::ceil(1.5 / TIME_H));              //! Connection delay - in timesteps

#endif //BRUNEL_CONSTANTS_H
