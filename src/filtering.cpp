#include "filtering.h"
#include <complex>
#include <vector>
#include <cmath>
#include <numbers>

// Discrete Fourier Transform (DFT) implementation
std::vector<std::complex<double>> dft(const std::vector<double>& signal) {

    // initiate result vector of same size
    int N = signal.size();
    std::vector<std::complex<double>> result(N);

    // loop through frequencies
    for (int k = 0; k < N; k++) {
        result[k] = 0;

        // loop through data points
        for (int n = 0; n < N; n++) {

            // perform dft and sum
            double angle = -2.0 * std::numbers::pi * k * n / N;
            result[k] += signal[n] * 
            std::complex<double>(std::cos(angle), std::sin(angle));
        }
    }
    return result;
}

// Inverse Discrete Fourier Transform (IDFT) implementation
std::vector<double> idft(const std::vector<std::complex<double>>& freqs) {

    // initiate result vector of same size
    int N = freqs.size();
    std::vector<double> result(N);

    // loop through data points
    for (int n = 0; n < N; n++) {
        std::complex<double> sum = 0;

        // loop through frequency signal
        for (int k = 0; k < N; k++) {

            // perform idft and sum
            double angle = 2.0 * std::numbers::pi * k * n / N;
            sum += freqs[k] * std::complex<double>(std::cos(angle), std::sin(angle));
        }

        result[n] = sum.real() / N;
    }
    return result;
}

// apply Ram-Lak filter to a single sinogram row
std::vector<double> ramLakFilter(const std::vector<double>& row) {

    // perform dft
    int N = row.size();
    std::vector<std::complex<double>> freqs = dft(row);

    // apply filter and window
    for (int k = 0; k < N; k++) {
        double freq = (k <= N / 2) ? k : N - k;
        double hann = 0.5 * (1 + std::cos(std::numbers::pi * freq / (N / 2)));
        freqs[k] *= freq * hann;
    }

    // perform idft
    return idft(freqs);
}

// run the Ram-Lak filter on the entire sinogram
std::vector<std::vector<double>> filteredSinogram(const std::vector<std::vector<double>>& sinogram) {

    // initialize grid to populate the filtered sinogram
    std::vector<std::vector<double>> filtered(sinogram.size(), std::vector<double>(sinogram[0].size()));

    // filter each row
    for (size_t row = 0; row < sinogram.size(); row++) {
        filtered[row] = ramLakFilter(sinogram[row]);
    }

    return filtered;
}