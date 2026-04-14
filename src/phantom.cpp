#include "phantom.h"
#include <cmath>
#include <tuple>


std::tuple<double, double> normalizeCoordinates(int i, int j, int size) {
    double x = (2.0 * j / size) - 1.0;
    double y = (2.0 * i / size) - 1.0;
    return {x, y};
}

void generatePhantom(std::vector<std::vector<double>>& image, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Normalize coordinates to range [-1, 1]
            auto [x, y] = normalizeCoordinates(i, j, size);

            image[i][j] = 0.0;

            // Outer ellipse (skull)
            if ((x * x) / 0.69 + (y * y) / 0.92 <= 1.0)
                image[i][j] += 1.0;

            // Inner ellipse (brain matter)
            if ((x * x) / 0.6624 + (y * y) / 0.8740 <= 1.0)
                image[i][j] -= 0.98;

            // Small detail ellipse
            if (((x - 0.22) * (x - 0.22)) / 0.11 + (y * y) / 0.31 <= 1.0)
                image[i][j] += 0.41;
        }
    }
}

void generateCirclePhantom(std::vector<std::vector<double>>& image, int size) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            auto [x, y] = normalizeCoordinates(i, j, size);
            image[i][j] = 0.0;
            if (x * x + y * y <= 0.5)
                image[i][j] = 1.0;
        }
    }
}

void generateOffCenterPhantom(std::vector<std::vector<double>>& image, int size) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            auto [x, y] = normalizeCoordinates(i, j, size);

            image[i][j] = 0.0;

            if ((x+0.4) * (x+0.4) / 0.25 + (y+0.4) * (y+0.4) / 0.4 <= 0.7) {
                image[i][j] = 1.0;
            }

            if ((x-0.3) * (x-0.3) / 0.1 + (y-0.3) * (y-0.3) / 0.1 <= 1.0) {
                image[i][j] = 1.0;
            }

            if ((x * x + y * y <= 0.25) && (x * x + y * y >= 0.20)) {
                image[i][j] = 1.0;
            }
        }
    }
}