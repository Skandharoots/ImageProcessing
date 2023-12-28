#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <iostream>
#include "IFFT.h"
#include "CImg.h"

using namespace cimg_library;
typedef std::complex<double> dcomp;

IFFT::IFFT(std::string inputPath, std::string outputPath, std::string inputPath2) {

	this->inputPath = inputPath;
	this->outputPath = outputPath;
    this->inputPath2 = inputPath2;
}

IFFT::~IFFT() {
}

std::string IFFT::getInputPath() {
	return this->inputPath;
}
void IFFT::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string IFFT::getInputPath2() {
	return this->inputPath2;
}
void IFFT::setInputPath2(std::string path) {
	this->inputPath2 = path;
}

std::string IFFT::getOutputPath() {
	return this->outputPath;
}

void IFFT::setOutputPath(std::string path) {
	this->outputPath = path;
}

void IFFT::transform() {

	cimg::exception_mode(0);
	try {
		CImg<unsigned char> magnitude(getInputPath().c_str());
		CImg<unsigned char> phase(getInputPath2().c_str());
        CImg<unsigned char> half(getInputPath().c_str());
        CImg<unsigned char> resultimage(getInputPath().c_str());
        double real = 0;
        double imaginary = 0;
        double result = 0;
        float avg = 0;
        float max = 0;
        for (int x = 0; x < magnitude.width(); x++) {
            for (int y = 0; y < magnitude.height(); y++) {
                if(magnitude(x, y, 0) > max) {
                    max = magnitude(x, y, 0); 
                }
            }
        }

        for (int x = 0; x < magnitude.width(); x++) {
            for (int y = 0; y < magnitude.height(); y++) {
                for (int xx = 0; xx < magnitude.width(); xx++) {
                    real += magnitude(xx, y, 0) * cos((2.0 * M_PI * (x - magnitude.width()/2) * xx) / magnitude.width());
                    imaginary += magnitude(xx, y, 0) * sin((2.0 * M_PI * (x - magnitude.width()/2) * xx) / magnitude.width());
                }
                result = (1/(2*M_PI))*sqrt(pow(real / magnitude.width(), 2) + pow(imaginary / magnitude.width(), 2));
                half(x, y, 0) = (255/log(1 + abs(max))) * log(1 + abs(result));
                half(x, y, 1) = (255/log(1 + abs(max))) * log(1 + abs(result));
                half(x, y, 2) = (255/log(1 + abs(max))) * log(1 + abs(result));
                real = 0;
                imaginary = 0;
                result = 0;
            }
        }
        for (int y = 0; y < magnitude.height(); y++) {
            for (int x = 0; x < magnitude.width(); x++) {
                for (int yy = 0; yy < magnitude.height(); yy++) {
                    real += magnitude(x, yy, 0) * cos((2.0 * M_PI * (y - magnitude.height()/2) * yy) / magnitude.height());
                    imaginary += magnitude(x, yy, 0) * -1 * sin((2.0 * M_PI * (y - magnitude.height()/2) * yy) / magnitude.height());
                }
                result = sqrt(pow(real / magnitude.height(), 2) + pow(imaginary / magnitude.height(), 2));
                resultimage(x, y, 0) = (255/log(1 + abs(max))) * log(1 + abs(result));
                resultimage(x, y, 1) = (255/log(1 + abs(max))) * log(1 + abs(result));
                resultimage(x, y, 2) = (255/log(1 + abs(max))) * log(1 + abs(result));
                real = 0;
                imaginary = 0;
                result = 0;
            }
        }
        resultimage.save_bmp(getOutputPath().c_str());
	}
	catch (CImgIOException e) {
		throw std::exception("Cannot load or save from the path. Path invalid.\n");
	}
}