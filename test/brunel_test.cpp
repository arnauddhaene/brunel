//
// Created by Arnaud Dhaene on 16.10.17.
//

#include "../googletest/include/gtest/gtest.h"
#include <iostream>
#include "../src/Neuron.h"
#include "../src/Buffer.h"
#include "../src/Current.h"
#include "../src/Simulation.h"
#include "../src/constants.h"

constexpr float EPSILON = 1E-9;

/*
 * @brief test verifying that :
 * neuron spikes at correct times
 * refractory period is respected
 * potential restarts after refractory period
 * neuron doesn't spike when current is equal to 1
 */
TEST(NeuronTest, MembranePotential) {

    Simulation simulation(1); //! we will test with 1 neuron for the membrane test

    /// case that current is 1 picoAmper

    simulation.setCurrent(1, 0, 0, 500);

    std::vector<Neuron*>* neurons = simulation.run(0, 500);

    EXPECT_LT(abs((*neurons)[0]->getSpikesNumber()), EPSILON);
    EXPECT_GT(fabs(simulation.getNeuronV(0)[2580] - 20), EPSILON);
    EXPECT_LT(fabs((*neurons)[0]->getMembraneV(5000) - 20), EPSILON);

    /// case that current is 1.1 picoAmper

    Simulation simulation1(1);

    simulation1.setCurrent(1.1, 0, 0, 500);

    std::vector<Neuron*>* neurons1 = simulation1.run(0, 500);

    /// Spike number
    EXPECT_LT(abs((*neurons1)[0]->getSpikesNumber() - 10), EPSILON);

    /// Spike 1
    EXPECT_LT(fabs(simulation1.getNeuronV(0)[480] - 20), EPSILON);
    for(unsigned int i(481); i < (481 + C::REFRACTORY_TIME); ++i) {
        EXPECT_LT(fabs(simulation1.getNeuronV(0)[i]), EPSILON);
    }
    EXPECT_GT(fabs(simulation1.getNeuronV(0)[481 + C::REFRACTORY_TIME + 1]), EPSILON);

    /// Spike 2
    EXPECT_LT(fabs(simulation1.getNeuronV(0)[980] - 20), EPSILON);
    for(unsigned int i(981); i < (980 + C::REFRACTORY_TIME); ++i) {
        EXPECT_LT(fabs(simulation1.getNeuronV(0)[i]), EPSILON);
    }
    EXPECT_GT(fabs(simulation1.getNeuronV(0)[981 + C::REFRACTORY_TIME + 1]), EPSILON);

}

/*
 * @brief test verifying that :
 * current respects start and stop times
 * sends correct unvarying current value
 */
TEST(NeuronTest, Current) {

    /// Current instance
    Simulation simulation(1);

    simulation.setCurrent(1.5, 0, 0, 400);

    std::vector<Neuron*>* neurons = simulation.run(0, 1000);


    /// Testing value variation in Simulation to check if simulation does not affect current
    for(unsigned int i(0); i < 4000; ++i) {
        EXPECT_LT(fabs(simulation.getCurrent(0, i) - 1.5), EPSILON);
    }
    for(unsigned int j(4001); j < 10000; ++j) {
        EXPECT_LT(fabs(simulation.getCurrent(0, j)), EPSILON);
    }

}

/*
 * @brief test verifying that :
 * simulation does not affect buffer size
 * buffer erases value after transmitting spike
 */
TEST(NeuronTest, Buffer) {

    /// Instance
    Simulation simulation(2);

    simulation.setCurrent(1.1, 0, 0, 400);
    simulation.setCurrent(0, 1, 0, 400);

    Buffer* buffer = simulation.getNeuron(0)->getBuffer();

    /* Making sure that simulation does not affect buffer size
     * as delay between neuronal connections is constant throughout
     * our simulation. This way, each transmitted spike has the same
     * delay, defined in the constants file.
     */

    /// we start simulation until first spike and verify that buffer size does not change
    for(unsigned int i(0); i < 481; ++i) {
        simulation.loop();
        ///EXPECT_EQ(buffer->size(), C::DELAY + 1);
    }
    /// Spike 1 occurs at time 480 - neuron resets at time 481

    /// we verify that neuron writes into buffer of other neuron
    EXPECT_LT(simulation.getNeuron(1)->getBuffer()->amplitude(480 + C::DELAY, true) - C::J_AMP_EXCITATORY, EPSILON);

    /// we then continue simulation - without exceding buffer size
    for(unsigned int i(480); i < 480 + C::DELAY; ++i) {
        simulation.loop();
        EXPECT_EQ(buffer->size(), C::DELAY + 1);
    }

    /// verifying that buffer erases transmitted spike
    EXPECT_LT(simulation.getNeuron(1)->getBuffer()->amplitude(480 + C::DELAY, true), EPSILON);

}

/*
 * @brief test veryfying that:
 * neuron 0 transmits spike to neuron 1 with appropriate delay
 * neuron 1, having inCurrent of 1, spikes at reception of spike
 * neuron 1 transmits spik to neuron 2
 */
TEST(SimulationTest, ConnectionTransmittance) {

    /// Instance
    Simulation simulation(3);

    simulation.setCurrent(1.1, 0, 100, 200);
    simulation.setCurrent(1, 1, 0, 500);
    simulation.setCurrent(0, 2, 0, 500);

    simulation.getNeuron(0)->setConnection(1);
    simulation.getNeuron(1)->setConnection(2);

    std::vector<Neuron*>* neurons = simulation.run(0, 500);

	/// Spike 1
    EXPECT_LT(fabs(simulation.getNeuronV(0)[1480] - 20), EPSILON);
    EXPECT_LT(fabs(simulation.getNeuronV(0)[1481]), EPSILON);
    EXPECT_GT(fabs(simulation.getNeuronV(0)[1481 + C::REFRACTORY_TIME + 1]), EPSILON);

	/// Spike 1 Transmission to neuron 1 - will spike to 1st transmission
    EXPECT_LT(fabs(simulation.getNeuronV(1)[1480 + C::DELAY] - 20), EPSILON);
    EXPECT_GT(fabs(simulation.getNeuronV(1)[1482 + C::DELAY + C::REFRACTORY_TIME + 1]), EPSILON);
    
    /// Spike Transmission to neuron 2 - small spike (0.1 mV)
    EXPECT_LT(fabs(simulation.getNeuronV(2)[1480 + 2 * C::DELAY] - 0.1), EPSILON);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
