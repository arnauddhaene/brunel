//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_CONSTANTS_H
#define BRUNEL_CONSTANTS_H

constexpr double REFRACTORY_TIME = 2; // refractory period in which a neuron's potential zeroes after surpassing the threshold
constexpr double TIME_H = 0.1; // time variable in ms h that we will add at each incrementation
constexpr double V_RESET = -70; // en mV
constexpr double TAU = 10; // time constant : tau = RC
constexpr double CAPACITOR_C = 250; // value in pF
constexpr double RESISTANCE = TAU/CAPACITOR_C;
constexpr double THRESHOLD = -55; // in mV

#endif //BRUNEL_CONSTANTS_H
