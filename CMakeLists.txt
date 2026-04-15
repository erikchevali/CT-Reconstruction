cmake_minimum_required(VERSION 3.10)
project(CTReconstruction)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_BUILD_TYPE Debug)  # Set default build type to Debug

include_directories(include)

add_executable(ct_reconstruct
    src/main.cpp
    src/phantom.cpp
    src/projection.cpp
    src/reconstruction.cpp
    src/filtering.cpp
)
