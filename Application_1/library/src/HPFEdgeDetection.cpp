#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include <memory>
#include "HPFEdgeDetection.h"
#include "CImg.h"
#include "FastFourierTransform.h"

using namespace cimg_library;

HPFEdgeDetection::HPFEdgeDetection(std::string arguments, std::string inputPath, std::string outputPath, std::string inputPath2) {
    this->arguments = arguments;
	this->inputPath = inputPath;
	this->outputPath = outputPath;
    this->inputPath2 = inputPath2;

}

void HPFEdgeDetection::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string HPFEdgeDetection::getArguments() {
	return this->arguments;
}

HPFEdgeDetection::~HPFEdgeDetection() {
}

std::string HPFEdgeDetection::getInputPath() {
	return this->inputPath;
}

void HPFEdgeDetection::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string HPFEdgeDetection::getInputPath2() {
	return this->inputPath2;
}

void HPFEdgeDetection::setInputPath2(std::string path) {
	this->inputPath2 = path;
}

std::string HPFEdgeDetection::getOutputPath() {
	return this->outputPath;
}

void HPFEdgeDetection::setOutputPath(std::string path) {
	this->outputPath = path;
}

void HPFEdgeDetection::pass() {
	cimg::exception_mode(0);
	try {
        CImg<unsigned char> image(getInputPath().c_str());
        CImg<unsigned char> mask(getInputPath2().c_str());

        std::shared_ptr<FastFourierTransform> fft = std::make_shared<FastFourierTransform>(getInputPath().c_str(), getOutputPath().c_str());

        std::vector<std::vector<std::complex<double>>> matrix;
        std::vector<std::vector<std::complex<double>>> result;
        std::vector<std::vector<std::complex<double>>> filter(image.width(), std::vector<std::complex<double>>(image.height(), 0.0));

        double cutoffFrequency = stod(getArguments());

        for (int y = 0; y < image.height(); y++) {
            for (int x = 0; x < image.width(); x++) {
                int xx = abs(image.width()/2 - x);
                int yy = abs(image.height()/2 - y);
                if(sqrt((xx * xx) + (yy * yy)) > cutoffFrequency) {
                    filter[x][y] = 1.0;
                }

            }
        }

        matrix = fft->forward();

        double max = 0.0;
        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double magnitude = sqrt(pow(matrix[x][y].real(), 2) + pow(matrix[x][y].imag(), 2));
                if (magnitude > max) {
                    max = magnitude;
                }
            }
        }
        double c = 255 / log(1 + abs(max));

        fft->drawSpectrum(matrix, "../../../images/fftmag.bmp", c);


        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                matrix[x][y] *= filter[x][y];
            }
        }

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                if (mask(x, y, 0) == 0) {
                    matrix[x][y] *= 0.0;
                } else {
                    matrix[x][y] *= 1.0;
                }
            }
        }

        fft->drawSpectrum(matrix, "../../../images/hpfedmag.bmp", c);

        result = fft->inverse(matrix);

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double pls = result[x][y].real();
                if ((pls + 128) > 255) {
                    image(x, y, 0) = 255;
                    image(x, y, 1) = 255;
                    image(x, y, 2) = 255;
                }
                else if ((pls + 128) < 0) {
                    image(x, y, 0) = 0;
                    image(x, y, 1) = 0;
                    image(x, y, 2) = 0;
                }
                else {
                    image(x, y, 0) = pls + 128;
                    image(x, y, 1) = pls + 128;
                    image(x, y, 2) = pls + 128;
                }
            }
        }
        image.save_bmp(getOutputPath().c_str());
	}
	catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}

}