cmake_minimum_required(VERSION 3.9)

project(VirtualMemorySimulation VERSION 1.0.0 DESCRIPTION "Virtual Memory Simulation for CS1550")
include_directories(include/)

set(VIRTUAL_MEMORY_SIM_SRC
    src/main.cpp
    src/virtualMemorySimulation.cpp
    src/fifoAlgorithm.cpp
    src/secondAlgorithm.cpp
)

add_executable(vmsim ${VIRTUAL_MEMORY_SIM_SRC})