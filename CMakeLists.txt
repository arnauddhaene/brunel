cmake_minimum_required(VERSION 3.8)
project(brunel)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        README.md neuron.cpp neuron.h source/main.cpp source/Simulation.cpp source/Simulation.h)

add_executable(brunel ${SOURCE_FILES} neuron.cpp neuron.h source/Simulation.cpp source/Simulation.h)