#include <string>
#include <math.h>
#include <iostream>
#include <iomanip>
#include "CImg.h"
#include "SignalToNoiseRatio.h"

using namespace cimg_library;


SignalToNoiseRatio::SignalToNoiseRatio(std::string oryginalFile, std::string processedFile) {
    this->oryginalFile = oryginalFile;
    this->processedFile = processedFile;
}

SignalToNoiseRatio::~SignalToNoiseRatio() {

}

std::string SignalToNoiseRatio::getOryginalFile() {
    return this->oryginalFile;
}

void SignalToNoiseRatio::setOryginalFile(std::string path) {
    this->oryginalFile = path;
}

std::string SignalToNoiseRatio::getProcessedFile() {
    return this->processedFile;
}

void SignalToNoiseRatio::setProcessedFile(std::string path) {
    this->processedFile = path;
}


void SignalToNoiseRatio::calculate() {
    try {
        CImg<unsigned char> oryginal(getOryginalFile().c_str());
        CImg<unsigned char> processed(getProcessedFile().c_str());
        float error = 0;
        float snr = 0;
        float sumOr = 0;
        float sumOrPro = 0;
        for (int x = 0; x < oryginal.width(); x++) {
                for (int y = 0; y < oryginal.height(); y++) {
                    float oryginalSum = oryginal(x, y, 0);
                    oryginalSum += oryginal(x, y, 1);
                    oryginalSum += oryginal(x, y, 2);
                    float processedSum = processed(x, y, 0);
                    processedSum += processed(x, y, 1);
                    processedSum += processed(x, y, 2);
                    sumOr += oryginalSum / 3;
                    sumOrPro += ((oryginalSum / 3) - (processedSum / 3)); 
                }
        }
        snr = 10 * log10((sumOr * sumOr) / (sumOrPro * sumOrPro));
        std::cout << "Signal to noise ratio is: " << std::fixed << snr << std::setprecision(5) << std::endl;
    } catch (CImgIOException e) {
        throw std::exception("Input paths are invalid.\n");
    }
}