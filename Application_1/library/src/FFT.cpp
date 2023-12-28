#define _USE_MATH_DEFINES


#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <iostream>
#include "FFT.h"
#include "CImg.h"

using namespace cimg_library;

FFT::FFT(std::string inputPath, std::string outputPath, std::string outputPath2) {

	this->inputPath = inputPath;
	this->outputPath = outputPath;
    this->outputPath2 = outputPath2;
}

FFT::~FFT() {
}

std::string FFT::getInputPath() {
	return this->inputPath;
}
void FFT::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string FFT::getOutputPath() {
	return this->outputPath;
}

void FFT::setOutputPath(std::string path) {
	this->outputPath = path;
}

std::string FFT::getOutputPath2() {
	return this->outputPath2;
}

void FFT::setOutputPath2(std::string path) {
	this->outputPath2 = path;
}

void FFT::transform() {

	cimg::exception_mode(0);
	try {
		CImg<unsigned char> image(getInputPath().c_str());
		CImg<unsigned char> image2(getInputPath().c_str());
        CImg<unsigned char> image3(getInputPath().c_str());
        CImg<unsigned char> phase1(getInputPath().c_str());
        CImg<unsigned char> phase2(getInputPath().c_str());

        float real = 0;
        float imaginary = 0;
        float result = 0;
        float phase = 0;
        float avg = 0;
        float max = 0;
        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                avg = (image(x, y, 0) + image(x, y, 1) + image(x, y, 2)) / 3;
                image(x, y, 0) = avg;
                image(x, y, 1) = avg;
                image(x, y, 2) = avg;
                avg = 0;
                if(image(x, y, 0) > max) {
                    max = image(x, y, 0); 
                }
            }
        }

        for (int y = 0; y < image.height(); y++) {
            for (int x = 0; x < image.width(); x++) {
                for (int yy = 0; yy < image.height(); yy++) {
                    real += image(x, yy, 0) * cos((2.0 * M_PI * y * yy) / image.height());
                    imaginary += image(x, yy, 0) * -1 * sin((2.0 * M_PI * y * yy) / image.height());
                }
                result = sqrt(pow(real / image.height(), 2) + pow(imaginary / image.height(), 2));
                image2(x, y, 0) = (255/log(1 + abs(max))) * log(1 + abs(result));
                image2(x, y, 1) = (255/log(1 + abs(max))) * log(1 + abs(result));
                image2(x, y, 2) = (255/log(1 + abs(max))) * log(1 + abs(result));
                if(real > 0 || imaginary != 0) {
                    phase = 2 * atan(imaginary / (real + sqrt(pow(real, 2) + pow(imaginary, 2))));
                    phase1(x, y, 0) = phase;
                    phase1(x, y, 1) = phase;
                    phase1(x, y, 2) = phase;
                } else if (real < 0 && imaginary == 0) {
                    phase = M_PI;
                    phase1(x, y, 0) = phase;
                    phase1(x, y, 1) = phase;
                    phase1(x, y, 2) = phase;
                } else {
                    phase = phase;
                }
                real = 0;
                imaginary = 0;
                result = 0;
            }
        }
        real = 0;
        imaginary = 0;
        result = 0;
        for (int x = 0; x < image2.width(); x++) {
            for (int y = 0; y < image2.height(); y++) {
                for (int xx = 0; xx < image2.width(); xx++) {
                    real += image2(xx, y, 0) * cos((2.0 * M_PI * x * xx) / image2.width());
                    imaginary += image2(xx, y, 0) * -1 * sin((2.0 * M_PI * x * xx) / image2.width());
                }
                result = sqrt(pow(real / image2.width(), 2) + pow(imaginary / image2.width(), 2));
                image3(x, y, 0) = (255/log(1 + abs(max))) * log(1 + abs(result));
                image3(x, y, 1) = (255/log(1 + abs(max))) * log(1 + abs(result));
                image3(x, y, 2) = (255/log(1 + abs(max))) * log(1 + abs(result));
                if(real > 0 || imaginary != 0) {
                    phase = 2 * atan(imaginary / (real + sqrt(pow(real, 2) + pow(imaginary, 2))));
                    phase1(x, y, 0) = phase;
                    phase1(x, y, 1) = phase;
                    phase1(x, y, 2) = phase;
                } else if (real < 0 && imaginary == 0) {
                    phase = M_PI;
                    phase1(x, y, 0) = phase;
                    phase1(x, y, 1) = phase;
                    phase1(x, y, 2) = phase;
                } else {
                    phase = phase;
                }
                real = 0;
                imaginary = 0;
                result = 0;
            }
        }
        for (int x = 0; x < image.width() / 2; x++) {
            for (int y = 0; y < image.height() / 2; y++) {
                image2(x + (image.width()/2), y + (image.height()/2), 0) = image3(x, y, 0);
                image2(x + (image.width()/2), y + (image.height()/2), 1) = image3(x, y, 1);
                image2(x + (image.width()/2), y + (image.height()/2), 2) = image3(x, y, 2);
                phase2(x + (image.width()/2), y + (image.height()/2), 0) = phase1(x, y, 0);
                phase2(x + (image.width()/2), y + (image.height()/2), 1) = phase1(x, y, 1);
                phase2(x + (image.width()/2), y + (image.height()/2), 2) = phase1(x, y, 2);
            }
        }
        for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
            for (int y = 0; y < image.height() / 2; y++) {
                image2(x - (image.width()/2), y + (image.height()/2), 0) = image3(x, y, 0);
                image2(x - (image.width()/2), y + (image.height()/2), 1) = image3(x, y, 1);
                image2(x - (image.width()/2), y + (image.height()/2), 2) = image3(x, y, 2);
                phase2(x - (image.width()/2), y + (image.height()/2), 0) = phase1(x, y, 0);
                phase2(x - (image.width()/2), y + (image.height()/2), 1) = phase1(x, y, 1);
                phase2(x - (image.width()/2), y + (image.height()/2), 2) = phase1(x, y, 2);
            }
        }
        for (int x = 0; x < image.width() / 2; x++) {
            for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
                image2(x + (image.width()/2), y - (image.height()/2), 0) = image3(x, y, 0);
                image2(x + (image.width()/2), y - (image.height()/2), 1) = image3(x, y, 1);
                image2(x + (image.width()/2), y - (image.height()/2), 2) = image3(x, y, 2);
                phase2(x + (image.width()/2), y - (image.height()/2), 0) = phase1(x, y, 0);
                phase2(x + (image.width()/2), y - (image.height()/2), 1) = phase1(x, y, 1);
                phase2(x + (image.width()/2), y - (image.height()/2), 2) = phase1(x, y, 2);
            }
        }
        for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
            for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
                image2(x - (image.width()/2), y - (image.height()/2), 0) = image3(x, y, 0);
                image2(x - (image.width()/2), y - (image.height()/2), 1) = image3(x, y, 1);
                image2(x - (image.width()/2), y - (image.height()/2), 2) = image3(x, y, 2);
                phase2(x - (image.width()/2), y - (image.height()/2), 0) = phase1(x, y, 0);
                phase2(x - (image.width()/2), y - (image.height()/2), 1) = phase1(x, y, 1);
                phase2(x - (image.width()/2), y - (image.height()/2), 2) = phase1(x, y, 2);
            }
        }
		image2.save_bmp(getOutputPath().c_str());
        phase2.save_bmp(getOutputPath2().c_str());
	}
	catch (CImgIOException e) {
		throw std::exception("Cannot load or save from the path. Path invalid.\n");
	}
}