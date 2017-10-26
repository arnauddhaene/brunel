//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_CONSTANTS_H
#define BRUNEL_CONSTANTS_H

namespace C {

    /// Simulation specific constants
    constexpr double TIME_H = 0.1;                      //! Time increment value - in ms
    constexpr unsigned long TIME_CONVERTER = 10;        //! Instead of dividing by TIME_H, we multiply by this
    constexpr unsigned long SIMULATION_SIZE = 12500;    //! Total number of neurons

    /// Connection constants
    constexpr unsigned int N_EXCITATORY = 10000;                   //! Total number of excitatory neurons
    constexpr unsigned int N_INHIBITORY = 2500;                    //! Total number of inhibitory neurons
    constexpr unsigned int C_EXCITATORY = 1000;                    //! Number of excitatory connections per neuron
    constexpr unsigned int C_INHIBITORY = 250;                     //! Number of inhibitory connections per neuron
    constexpr double J_AMP_EXCITATORY = 0.1;                       //! Connection spike amplitude in mV
    constexpr double J_AMP_INHIBITORY =  - J_AMP_EXCITATORY * 5;   //! Spike transmission Amplitude for inhibitory neurons
    constexpr unsigned long DELAY = 15;                            //! Delay of spike transmission

    /// Neuron specific constants
    constexpr double TAU = 20.0;                            //! Neuron Tau time constant : tau = RC - in ms
    constexpr double CAPACITOR_C = 1.0;                     //! Neuron Capacitor value - in pF
    constexpr double RESISTANCE = TAU / CAPACITOR_C;        //! Neuron resistance value - in ms/pF
    constexpr double V_THRESHOLD = 20.0;                    //! Neuron threshold value - in mV
    constexpr double V_RESET = 0.0;                         //! Neuron inactive potential - in mV
    constexpr unsigned long REFRACTORY_TIME = 2 * TIME_CONVERTER;  // ! Neuron refractory period - in timesteps
    constexpr double V_EXT = 2 * V_THRESHOLD / (C_EXCITATORY * J_AMP_EXCITATORY * TAU); // External frequency in MHz

}

#endif //BRUNEL_CONSTANTS_H
