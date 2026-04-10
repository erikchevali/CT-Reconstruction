#include "projection.h"
#include <cmath>
#include <numbers>

void generateSinogram(
    const std::vector<std::vector<double>>& image,
    std::vector<std::vector<double>>& sinogram,
    int numAngles,
    int numSensors,
    int length, 
    double tStep, 
    double r) {
 

    int width = image[0].size();
    int height = image.size();
    double maxDiag = std::sqrt(width * width + height * height);
    double halfLength = numSensors / 2.0;
    double centerX = width / 2.0;
    double centerY = height / 2.0;
    double dTheta = 2 * std::numbers::pi / numAngles;

        for (int i = 0; i < numAngles; ++i) {
            
            double theta = i * (2 * std::numbers::pi) / numAngles;
            double cosT = std::cos(theta);
            double sinT = std::sin(theta);
            
            double rx = r * sinT;
            double ry = r * cosT;


            for (int s = 0; s < numSensors; ++s) {
                
                // puts the sensor location in a range from -1 to 1
                double normS = (s - halfLength) / halfLength;

                // scale to the sensor length
                normS = normS * length;

                double raySum = 0.0;

                double sx = normS * cosT;
                double sy = normS * sinT;

                for (double t = 0; t < maxDiag; t+=tStep){
                    
                    int x = std::round(centerX + rx + sx - t * sinT);
                    int y = std::round(centerY - ry + sy + t * cosT);
                    if (x < width && x >= 0 && y < height && y >= 0){
                        raySum += image[y][x];
                    } 

                } 

                sinogram[i][s] = raySum;
              
            }
        }

}







   