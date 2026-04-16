#include "projection.h"
#include <cmath>
#include <numbers>

// generate sinogram from a phantom image
void generateSinogram(
    const std::vector<std::vector<double>>& image,
    std::vector<std::vector<double>>& sinogram,
    int numAngles,
    int numSensors,
    int length, 
    double tStep, 
    double r) {

    // find the dimensions of the phantom
    int width = image[0].size();
    int height = image.size();

    // calculate the longest path across the phantom
    double maxDiag = std::sqrt(width * width + height * height);

    // half sensor number for normalization
    double halfLength = numSensors / 2.0;

    // calculate the center of the image
    double centerX = width / 2.0;
    double centerY = height / 2.0;

    // calculate the angle step size
    double dTheta = 2 * std::numbers::pi / numAngles;

    // loop through angles
    for (int i = 0; i < numAngles; ++i) {
        
        // calculate the angle in radians, and pre-calculate sin and cos
        double theta = i * (2 * std::numbers::pi) / numAngles;
        double cosT = std::cos(theta);
        double sinT = std::sin(theta);
        
        // calculate the bar revolution radius contribution to position
        double rx = r * sinT;
        double ry = r * cosT;

        // loop through sensors
        for (int s = 0; s < numSensors; ++s) {
            
            // normalize to [-1, 1]
            double normS = (s - halfLength) / halfLength;

            // scale to the bar length
            normS = normS * length;

            // calculate sensor location contribution to position
            double sx = normS * cosT;
            double sy = normS * sinT;

            double raySum = 0.0;

            // loop through ray steps
            for (double t = 0; t < maxDiag; t+=tStep){
                
                // calulate the fixed axis position in the ray
                int x = std::round(centerX + rx + sx - t * sinT);
                int y = std::round(centerY - ry + sy + t * cosT);

                // sum the attenuation at the current position
                if (x < width && x >= 0 && y < height && y >= 0){
                    raySum += image[y][x];
                } 
            } 

            sinogram[i][s] = raySum;
            
        }
    }
}







   