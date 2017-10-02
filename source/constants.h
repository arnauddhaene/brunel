//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_CONSTANTS_H
#define BRUNEL_CONSTANTS_H

// Simulation specific constants
constexpr double TIME_H = 0.1;                  // Time increment value - in ms

// Neuron specific constants
constexpr double TAU = 10;                      // Neuron Tau time constant : tau = RC - in ms
constexpr double CAPACITOR_C = 250;             // Neuron Capacitor value - in pF
constexpr double RESISTANCE = TAU/CAPACITOR_C;  // Neuron resistance value - in ms/pF
constexpr double THRESHOLD = -55;               // Neuron threshold value - in mV
constexpr double V_RESET = -70;                 // Neuron inactive potential - in mV
constexpr double REFRACTORY_TIME = 2;           // Neuron refractory period
                                                // during which the potential zeroes due to surpassing the threshold
constexpr double V_SPIKE = 0;                   // Neuron potential when it spikes - in mV

#endif //BRUNEL_CONSTANTS_H
