#pragma once
#include <vector>

std::vector<std::vector<double>> filteredSinogram(const std::vector<std::vector<double>>& sinogram);
std::vector<double> ramLakFilter(const std::vector<double>& row);