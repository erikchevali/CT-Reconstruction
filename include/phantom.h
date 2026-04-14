#pragma once
#include <vector>

void generatePhantom(std::vector<std::vector<double>>& image, int size);
void generateCirclePhantom(std::vector<std::vector<double>>& image, int size);
void generateOffCenterPhantom(std::vector<std::vector<double>>& image, int size);
void generateHighContrastPhantom(std::vector<std::vector<double>>& image, int size);
void generateMultiObjectPhantom(std::vector<std::vector<double>>& image, int size);