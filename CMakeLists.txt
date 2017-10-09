cmake_minimum_required(VERSION 3.8)
project(brunel)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        README.md src/Neuron.cpp src/Neuron.h src/main.cpp src/Simulation.cpp src/Simulation.h src/Current.cpp src/Current.h src/constants.h src/Buffer.cpp src/Buffer.h)

add_executable(brunel ${SOURCE_FILES} src/Neuron.cpp src/Neuron.h src/Simulation.cpp src/Simulation.h src/Current.cpp src/Current.h src/constants.h src/Buffer.cpp src/Buffer.h)