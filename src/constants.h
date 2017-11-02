//
// Created by Arnaud Dhaene on 02.10.17.
//

#ifndef BRUNEL_CONSTANTS_H
#define BRUNEL_CONSTANTS_H

namespace C {

    /*
     * Network specific constants
     */

    /// Time increment value - in ms
    constexpr double TIME_H = 0.1;

    /// Instead of dividing by TIME_H, we multiply by this for exactitude of results
    constexpr unsigned long TIME_CONVERTER = 10;

    /// Total number of neurons
    constexpr unsigned long SIMULATION_SIZE = 12500;
    constexpr unsigned long N_EXCITATORY = 10000;
    constexpr unsigned long N_INHIBITORY = 2500;

    /// Ratio of excitatory on inhibitory in total neurons
    constexpr double E_I_RATI0 = 0.8;

    /*
     * Connection specific constants
     */

    /// Ji / Je
    constexpr double G = 5.0;

    /// Number of excitatory and inhibitory incoming connections per neuron
    constexpr unsigned int C_EXCITATORY = 1000;
    constexpr unsigned int C_INHIBITORY = 250;
    constexpr unsigned int C_TOTAL = C_EXCITATORY + C_INHIBITORY;

    /// Spike transmission Amplitude for excitatory and inhibitory neurons
    constexpr double J_AMP_EXCITATORY = 0.1;
    constexpr double J_AMP_INHIBITORY =  - J_AMP_EXCITATORY * G;

    /// Delay of spike transmission - in timesteps
    constexpr unsigned long DELAY = 15;

    /*
     * Neuron specific constants
     */

    /// Neuron Tau time constant : tau = RC - in ms
    constexpr double TAU = 20.0;

    /// Neuron Capacitor value - in pF
    constexpr double CAPACITOR_C = 1.0;

    /// Neuron resistance value - in ms/pF
    constexpr double RESISTANCE = TAU / CAPACITOR_C;

    /// Neuron threshold value - in mV
    constexpr double V_THRESHOLD = 20.0;

    /// Neuron inactive potential - in mV
    constexpr double V_RESET = 0.0;

    /// Neuron refractory period - in timesteps
    constexpr unsigned long REFRACTORY_TIME = 2 * TIME_CONVERTER;

    /// Frequency of background spikes - in arriving spikes per timestep
    constexpr double ETA = 2.0;
    constexpr double NU_EXT = ETA * V_THRESHOLD / (TAU * J_AMP_EXCITATORY);
}

#endif //BRUNEL_CONSTANTS_H
