cmake_minimum_required(VERSION 2.6)
project(brunel)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        README.md src/Neuron.cpp src/Neuron.h src/main.cpp src/Network.cpp src/Network.h src/Current.cpp src/Current.h src/constants.h src/Buffer.cpp src/Buffer.h src/Experiment.cpp src/Experiment.h)

add_executable(brunel ${SOURCE_FILES} src/Neuron.cpp src/Neuron.h src/Network.cpp src/Network.h src/Current.cpp src/Current.h src/constants.h src/Buffer.cpp src/Buffer.h src/Experiment.cpp src/Experiment.h)

enable_testing()
add_subdirectory(googletest)
include_directories({$googletest_SOURCE_DIR}/include {$googletest_SOURCE_DIR})

add_executable(bruneltest src/Neuron.cpp src/Current.cpp src/Buffer.cpp src/Network.cpp test/brunel_test.cpp src/Experiment.cpp src/Experiment.h)
target_link_libraries(bruneltest gtest gtest_main)
add_test(bruneltest bruneltest)
