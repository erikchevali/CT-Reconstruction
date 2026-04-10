#pragma once
#include <vector>

void generateSinogram(
    const std::vector<std::vector<double>>& image,
    std::vector<std::vector<double>>& sinogram,
    int numAngles,
    int numSensors, 
    int length, 
    double tStep, 
    double r);