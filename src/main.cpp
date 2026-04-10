#include <numbers> 
#include <iostream>
#include <fstream>
#include "phantom.h"
#include "projection.h"


void savePGM(const std::vector<std::vector<double>>& image, int size, const std::string& filename) {
    std::ofstream file(filename);
    file << "P2\n" << size << " " << size << "\n255\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int val = static_cast<int>(image[i][j] * 255);
            if (val < 0) val = 0;
            if (val > 255) val = 255;
            file << val << " ";
        }
        file << "\n";
    }
}

void saveSinogramPGM(const std::vector<std::vector<double>>& sinogram, const std::string& filename) {
    if (sinogram.empty() || sinogram[0].empty()) return;

    int numAngles = sinogram.size();
    int numSensors = sinogram[0].size();
    std::ofstream file(filename);

    // Find the max value for normalization
    double maxVal = 0.0;
    for (const auto& row : sinogram) {
        for (double val : row) {
            if (val > maxVal) maxVal = val;
        }
    }

    file << "P2\n" << numSensors << " " << numAngles << "\n255\n";
    for (int i = 0; i < numAngles; i++) {
        for (int j = 0; j < numSensors; j++) {
            // Scale based on the max value found in the data
            int val = (maxVal > 0) ? static_cast<int>((sinogram[i][j] / maxVal) * 255) : 0;
            file << val << " ";
        }
        file << "\n";
    }
}

int main() {
    int size = 256;
    std::vector<std::vector<double>> image(size, std::vector<double>(size, 0.0));

    std::cout << "Generating phantom..." << std::endl;
    generatePhantom(image, size);

    std::cout << "Saving phantom to data/phantom.pgm..." << std::endl;
    savePGM(image, size, "../data/phantom.pgm");


    // 2. Sinogram Setup
    int numAngles = 360;    // How many views
    int numSensors = 400;   // How wide the detector bar is
    int length = 200;       // Physical size of detector
    double tStep = 0.5;     // Step size for ray marching
    double r = 200.0;       // Orbit radius
    
    // Pre-allocate the sinogram vector
    std::vector<std::vector<double>> sinogram(numAngles, std::vector<double>(numSensors, 0.0));

    std::cout << "Generating sinogram..." << std::endl;
    generateSinogram(image, sinogram, numAngles, numSensors, length, tStep, r);

    std::cout << "Saving sinogram to data/sinogram.pgm..." << std::endl;
    saveSinogramPGM(sinogram, "../data/sinogram.pgm");

    std::cout << "Done!" << std::endl;
    
    return 0;
}