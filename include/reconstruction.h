#pragma once
#include <vector>

void reconstructImage(
    const std::vector<std::vector<double>>& sinogram,
    std::vector<std::vector<double>>& result,
    int numAngles,
    int numSensors,
    int length, 
    double tStep, 
    double r);