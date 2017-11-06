cmake_minimum_required(VERSION 2.6)
project(brunel)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        README.md src/Neuron.cpp src/Neuron.h src/main.cpp src/Network.cpp src/Network.h src/Current.cpp src/Current.h src/constants.h src/Experiment.cpp src/Experiment.h)

add_executable(brunel ${SOURCE_FILES} src/Neuron.cpp src/Neuron.h src/Network.cpp src/Network.h src/Current.cpp src/Current.h src/constants.h src/Experiment.cpp src/Experiment.h)

enable_testing()
add_subdirectory(googletest)
include_directories({$googletest_SOURCE_DIR}/include {$googletest_SOURCE_DIR})

add_executable(bruneltest src/Neuron.cpp src/Current.cpp src/Network.cpp test/brunel_test.cpp src/Experiment.cpp src/Experiment.h)
target_link_libraries(bruneltest gtest gtest_main)
add_test(bruneltest bruneltest)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target(doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else (DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the doxygen documentation")
endif(DOXYGEN_FOUND)
