#include <string>
#include <iostream>
#include <math.h>
#include "GeometricMeanFilter.h"
#include "CImg.h"

using namespace cimg_library;

GeometricMeanFilter::GeometricMeanFilter(std::string inputPath, std::string outputPath) {
    this->inputPath = inputPath;
    this->outputPath = outputPath;
}

GeometricMeanFilter::~GeometricMeanFilter() {

}

std::string GeometricMeanFilter::getInputPath() {
	return this->inputPath;
}

void GeometricMeanFilter::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string GeometricMeanFilter::getOutputPath() {
	return this->outputPath;
}

void GeometricMeanFilter::setOutputPath(std::string path) {
	this->outputPath = path;
}

void GeometricMeanFilter::filter() {
    cimg::exception_mode(0);
	try {
        CImg<unsigned char> image(getInputPath().c_str());
        CImg<unsigned char> copy(getInputPath().c_str());
        float std_dev = 20;
        float sum0 = 1;
        float sum1 = 1;
        float sum2 = 1;
        for (int x = 1; x < copy.width() - 1; x++) {
                for (int y = 1; y < copy.height() - 1; y++) {
                        for (int i = x - 1; i < x + 2; i++) { //loop for the first x in box of 9
                            for (int j = y - 1; j < y + 2; j++) { // loop for the first y in box of 9
                                sum0 *= copy(i, j, 0);
                                sum1 *= copy(i, j, 1);
                                sum2 *= copy(i, j, 2); 
                            }
                        }
                        image(x, y, 0) = pow(sum0, 0.111111111);
                        image(x, y, 1) = pow(sum1, 0.111111111);
                        image(x, y, 2) = pow(sum2, 0.111111111);
                        sum0 = 1;
                        sum1 = 1;
                        sum2 = 1;
                }
            } 
        image.save_bmp(getOutputPath().c_str());
    }
    catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}
}