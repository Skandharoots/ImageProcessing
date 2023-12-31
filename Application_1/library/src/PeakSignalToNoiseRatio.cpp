#include <string>
#include <math.h>
#include <iostream>
#include <iomanip>
#include "CImg.h"
#include "PeakSignalToNoiseRatio.h"

using namespace cimg_library;


PeakSignalToNoiseRatio::PeakSignalToNoiseRatio(std::string oryginalFile, std::string processedFile) {
    this->oryginalFile = oryginalFile;
    this->processedFile = processedFile;
}

PeakSignalToNoiseRatio::~PeakSignalToNoiseRatio() {

}

std::string PeakSignalToNoiseRatio::getOryginalFile() {
    return this->oryginalFile;
}

void PeakSignalToNoiseRatio::setOryginalFile(std::string path) {
    this->oryginalFile = path;
}

std::string PeakSignalToNoiseRatio::getProcessedFile() {
    return this->processedFile;
}

void PeakSignalToNoiseRatio::setProcessedFile(std::string path) {
    this->processedFile = path;
}


void PeakSignalToNoiseRatio::calculate() {
    cimg::exception_mode(0);
    try {
        CImg<unsigned char> oryginal(getOryginalFile().c_str());
        CImg<unsigned char> processed(getProcessedFile().c_str());
        float snr = 0;
        float sum = 0;
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
                    sum += ((oryginalSum / 3) - (processedSum / 3));
                }
        }
        snr = 10 * log10(((max * max)*(oryginal.width() * oryginal.height())) / (sum * sum));
        std::cout << "Peak signal to noise ratio is: " << std::fixed << snr << std::setprecision(5) << " [dB]" << std::endl;
    } catch (CImgIOException e) {
        throw std::logic_error("Input paths are invalid.\n");
    }
}