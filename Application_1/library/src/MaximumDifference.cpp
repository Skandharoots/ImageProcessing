#include <string>
#include <math.h>
#include <iostream>
#include <iomanip>
#include "CImg.h"
#include "MaximumDifference.h"

using namespace cimg_library;


MaximumDifference::MaximumDifference(std::string oryginalFile, std::string processedFile) {
    this->oryginalFile = oryginalFile;
    this->processedFile = processedFile;
}

MaximumDifference::~MaximumDifference() {

}

std::string MaximumDifference::getOryginalFile() {
    return this->oryginalFile;
}

void MaximumDifference::setOryginalFile(std::string path) {
    this->oryginalFile = path;
}

std::string MaximumDifference::getProcessedFile() {
    return this->processedFile;
}

void MaximumDifference::setProcessedFile(std::string path) {
    this->processedFile = path;
}


void MaximumDifference::calculate() {
    cimg::exception_mode(0);
    try {
        CImg<unsigned char> oryginal(getOryginalFile().c_str());
        CImg<unsigned char> processed(getProcessedFile().c_str());
        float oryginalSumMax = 0;
        float processedSumMax = 0;
        float max = 0;
        for (int x = 0; x < oryginal.width(); x++) {
                for (int y = 0; y < oryginal.height(); y++) {
                    oryginalSumMax += oryginal(x, y, 0);
                    oryginalSumMax += oryginal(x, y, 1);
                    oryginalSumMax += oryginal(x, y, 2);
                    processedSumMax += processed(x, y, 0);
                    processedSumMax += processed(x, y, 1);
                    processedSumMax += processed(x, y, 2);
                    if (abs((oryginalSumMax / 3) - (processedSumMax / 3)) > max) {
                        max = abs((oryginalSumMax / 3) - (processedSumMax / 3));
                    }
                    oryginalSumMax = 0;
                    processedSumMax = 0; 
                }
        }
        std::cout << "Maximum difference is: " << std::fixed << max << std::setprecision(5) << std::endl;
    } catch (CImgIOException e) {
        throw std::exception("Input paths are invalid.\n");
    }
}