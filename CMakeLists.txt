cmake_minimum_required(VERSION 3.8)
project(brunel)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        README.md source/Neuron.cpp source/Neuron.h source/main.cpp source/Simulation.cpp source/Simulation.h source/Current.cpp source/Current.h source/constants.h)

add_executable(brunel ${SOURCE_FILES} source/Neuron.cpp source/Neuron.h source/Simulation.cpp source/Simulation.h source/Current.cpp source/Current.h source/constants.h)