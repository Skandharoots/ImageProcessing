#include <string>
#include <math.h>
#include <iostream>
#include <iomanip>
#include "CImg.h"
#include "PeakMeanSquareError.h"

using namespace cimg_library;


PeakMeanSquareError::PeakMeanSquareError(std::string oryginalFile, std::string processedFile) {
    this->oryginalFile = oryginalFile;
    this->processedFile = processedFile;
}

PeakMeanSquareError::~PeakMeanSquareError() {

}

std::string PeakMeanSquareError::getOryginalFile() {
    return this->oryginalFile;
}

void PeakMeanSquareError::setOryginalFile(std::string path) {
    this->oryginalFile = path;
}

std::string PeakMeanSquareError::getProcessedFile() {
    return this->processedFile;
}

void PeakMeanSquareError::setProcessedFile(std::string path) {
    this->processedFile = path;
}


void PeakMeanSquareError::calculate() {
    cimg::exception_mode(0);
    try {
        CImg<unsigned char> oryginal(getOryginalFile().c_str());
        CImg<unsigned char> processed(getProcessedFile().c_str());
        float sum_sq = 0;
        float mse = 0;
        float max = 0;
        for (int x = 0; x < oryginal.width(); x++) {
                for (int y = 0; y < oryginal.height(); y++) {
                    float oryginalSum = oryginal(x, y, 0);
                    oryginalSum += oryginal(x, y, 1);
                    oryginalSum += oryginal(x, y, 2);
                    if ((oryginalSum / 3) > max) {
                        max = oryginalSum / 3;
                    }
                    float processedSum = processed(x, y, 0);
                    processedSum += processed(x, y, 1);
                    processedSum += processed(x, y, 2);
                    float err = (oryginalSum / 3) - (processedSum / 3);
                    sum_sq += (err * err);
                }
        }
        mse = sum_sq / ((oryginal.height() * oryginal.width()) * (max * max));
        std::cout << "Peak Mean square error is: " << std::fixed << mse << std::setprecision(2) << std::endl;
    } catch (CImgIOException e) {
        throw std::exception("Input paths are invalid.\n");
    }
}