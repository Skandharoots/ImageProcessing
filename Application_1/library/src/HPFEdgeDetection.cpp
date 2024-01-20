#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
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
//	cimg::exception_mode(0);
//	try {
//        CImg<unsigned char> image(getInputPath().c_str());
//        CImg<unsigned char> mask(getInputPath2().c_str());
//        CImg<unsigned char> magnitude(getInputPath().c_str());
//        CImg<unsigned char> mag(getInputPath().c_str());
//
//        FastFourierTransform fft(getInputPath().c_str(), getOutputPath().c_str());
//
//        std::vector<std::complex<double>> matrix;
//        std::vector<std::complex<double>> transformOutput;
//        std::vector<std::complex<double>> transformCentered;
//        std::vector<std::complex<double>> resultDecentered;
//        std::vector<std::complex<double>> result;
//        std::vector<std::complex<double>> filter(image.width() * image.height(), 0.0);
//
//        double cutoffFrequency = stod(getArguments());
//
//        for (int y = 0; y < image.height(); y++) {
//            for (int x = 0; x < image.width(); x++) {
//                int index = y * image.width() + x;
//                int xx = abs(image.width()/2 - x);
//                int yy = abs(image.height()/2 - y);
//                if(sqrt((xx * xx) + (yy * yy)) > cutoffFrequency) {
//                    filter[index] = 1.0;
//                }
//
//            }
//        }
//
//        matrix = fft.forward();
//        transformOutput = fft.fft(matrix);
//        transformCentered = fft.center(transformOutput);
//
//        for (int x = 0; x < image.width(); x++) {
//            for (int y = 0; y < image.height(); y++) {
//                double magnitude = sqrt(pow(transformCentered[image.width() * x + y].real(), 2) + pow(transformCentered[image.width() * x + y].imag(), 2));
//                if (20 * log(1 + magnitude) < 0) {
//                    mag(x, y, 0) = 0;
//                    mag(x, y, 1) = 0;
//                    mag(x, y, 2) = 0;
//                } else if (20 * log(1 + magnitude) > 255) {
//                    mag(x, y, 0) = 255;
//                    mag(x, y, 1) = 255;
//                    mag(x, y, 2) = 255;
//                } else {
//                    mag(x, y, 0) = 20 * log(1 + magnitude);
//                    mag(x, y, 1) = 20 * log(1 + magnitude);
//                    mag(x, y, 2) = 20 * log(1 + magnitude);
//                }
//            }
//        }
//        mag.save_bmp("../../../../images/fftmag.bmp");
//
//        for (int i = 0; i < transformCentered.size(); i++) {
//            transformCentered[i] *= filter[i];
//        }
//
//        for (int x = 0; x < image.width(); x++) {
//            for (int y = 0; y < image.height(); y++) {
//                if (mask(x, y, 0) == 0) {
//                    transformCentered[image.width() * x + y] *= 0.0;
//                } else {
//                    transformCentered[image.width() * x + y] *= 1.0;
//                }
//            }
//        }
//
//        for (int x = 0; x < image.width(); x++) {
//            for (int y = 0; y < image.height(); y++) {
//                double mag = sqrt(pow(transformCentered[image.width() * x + y].real(), 2) + pow(transformCentered[image.width() * x + y].imag(), 2));
//                if (20 * log(1 + mag) < 0) {
//                    magnitude(x, y, 0) = 0;
//                    magnitude(x, y, 1) = 0;
//                    magnitude(x, y, 2) = 0;
//                } else if (20 * log(1 + mag) > 255) {
//                    magnitude(x, y, 0) = 255;
//                    magnitude(x, y, 1) = 255;
//                    magnitude(x, y, 2) = 255;
//                } else {
//                    magnitude(x, y, 0) = 20 * log(1 + mag);
//                    magnitude(x, y, 1) = 20 * log(1 + mag);
//                    magnitude(x, y, 2) = 20 * log(1 + mag);
//                }
//            }
//        }
//
//        magnitude.save_bmp("../../../../images/hpfedmag.bmp");
//
//        resultDecentered = fft.center(transformCentered);
//        result = fft.ifft(resultDecentered);
//
//        for (int x = 0; x < image.width(); x++) {
//            for (int y = 0; y < image.height(); y++) {
//                result[image.width() * x + y] = result[image.width() * x + y] / ((double) result.size());
//                double pls = result[image.width() * x + y].real();
//                if ((pls + 128) > 255) {
//                    image(x, y, 0) = 255;
//                    image(x, y, 1) = 255;
//                    image(x, y, 2) = 255;
//                }
//                else if ((pls + 128) < 0) {
//                    image(x, y, 0) = 0;
//                    image(x, y, 1) = 0;
//                    image(x, y, 2) = 0;
//                }
//                else {
//                    image(x, y, 0) = pls + 128;
//                    image(x, y, 1) = pls + 128;
//                    image(x, y, 2) = pls + 128;
//                }
//            }
//        }
//        image.save_bmp(getOutputPath().c_str());
//	}
//	catch (CImgIOException e) {
//		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
//	}

}