
#include <string>
#include <math.h>
#include <iostream>
#include <iomanip>
#include "CImg.h"
#include "MeanSquareError.h"

using namespace cimg_library;


MeanSquareError::MeanSquareError(std::string oryginalFile, std::string processedFile) {
    this->oryginalFile = oryginalFile;
    this->processedFile = processedFile;
}

MeanSquareError::~MeanSquareError() {

}

std::string MeanSquareError::getOryginalFile() {
    return this->oryginalFile;
}

void MeanSquareError::setOryginalFile(std::string path) {
    this->oryginalFile = path;
}

std::string MeanSquareError::getProcessedFile() {
    return this->processedFile;
}

void MeanSquareError::setProcessedFile(std::string path) {
    this->processedFile = path;
}


void MeanSquareError::calculate() {
    cimg::exception_mode(0);
    try {
        CImg<unsigned char> oryginal(getOryginalFile().c_str());
        CImg<unsigned char> processed(getProcessedFile().c_str());
        float sum_sq = 0;
        float mse = 0;
        for (int x = 0; x < oryginal.width(); x++) {
                for (int y = 0; y < oryginal.height(); y++) {
                    float oryginalSum = oryginal(x, y, 0);
                    oryginalSum += oryginal(x, y, 1);
                    oryginalSum += oryginal(x, y, 2);
                    float processedSum = processed(x, y, 0);
                    processedSum += processed(x, y, 1);
                    processedSum += processed(x, y, 2);
                    float err = (oryginalSum / 3) - (processedSum / 3);
                    sum_sq += (err * err);
                }
        }
        mse = sum_sq / (oryginal.height() * oryginal.width());
        std::cout << "Mean square error is: " << std::fixed << mse << std::setprecision(2) << std::endl;
    } catch (CImgIOException e) {
        throw std::exception("Input paths are invalid.\n");
    }
}