cmake_minimum_required(VERSION 3.10)
project(CTReconstruction)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(ct_reconstruct
    src/main.cpp
    src/phantom.cpp
    src/projection.cpp
    src/reconstruction.cpp
    src/filtering.cpp
)
