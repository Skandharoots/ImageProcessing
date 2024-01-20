#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include "PhaseModification.h"
#include "CImg.h"
#include "FastFourierTransform.h"

using namespace cimg_library;

PhaseModification::PhaseModification(std::string arguments, std::string inputPath, std::string outputPath) {
    this->arguments = arguments;
	this->inputPath = inputPath;
	this->outputPath = outputPath;

}

void PhaseModification::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string PhaseModification::getArguments() {
	return this->arguments;
}

PhaseModification::~PhaseModification() {
}

std::string PhaseModification::getInputPath() {
	return this->inputPath;
}
void PhaseModification::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string PhaseModification::getOutputPath() {
	return this->outputPath;
}

void PhaseModification::setOutputPath(std::string path) {
	this->outputPath = path;
}

void PhaseModification::pass() {
//	cimg::exception_mode(0);
//	try {
//        CImg<unsigned char> image(getInputPath().c_str());
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
//        std::complex<double> i;
//        i = -1;
//        i = sqrt(i);
//
//        std::string cutoffFrequencies = getArguments();
////        auto space = cutoffFrequencies.find(' ');
////        int k = stoi(cutoffFrequencies.substr(0, space));
////        int l = stoi(cutoffFrequencies.substr(space + 1));
//        std::stringstream ss(getArguments());
//        std::string del;
//        std::vector<std::string> v;
//        while (getline(ss, del, ' ')) {
//            v.push_back(del);
//        }
//        int k = stoi(v[0]);
//        int l = stoi(v[1]);
//        std::cout << k << " " << l << std::endl;
//
//        matrix = fft.forward();
//        transformOutput = fft.fft(matrix);
//        transformCentered = fft.center(transformOutput);
//
//        for (int y = 0; y < image.height(); y++) {
//            for (int x = 0; x < image.width(); x++) {
//                filter[image.height() * y + x] = exp(i * (((-x * k * 2.0 * M_PI) / image.width()) + ((-y * l * 2.0 * M_PI) / image.height()) + ((k + l) * M_PI)));
//                //std::cout << filter[image.height() * y + x] << std::endl;
//            }
//        }
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
//        magnitude.save_bmp("../../../../images/pmfmag.bmp");
//
//        for (int x = 0; x < filter.size(); x++) {
//            transformCentered[x] *= filter[x];
//        }
//
//        resultDecentered = fft.center(transformCentered);
//        result = fft.ifft(resultDecentered);
//
//        for (int x = 0; x < image.width(); x++) {
//            for (int y = 0; y < image.height(); y++) {
//                result[image.width() * x + y] = result[image.width() * x + y] / ((double) result.size());
////                double mag = sqrt(pow(result[image.width() * x + y].real(), 2) + pow(result[image.width() * x + y].imag(), 2));
////                mag = abs(mag);
//                if (abs(result[image.width() * x + y]) > 255) {
//                    image(x, y, 0) = 255;
//                    image(x, y, 1) = 255;
//                    image(x, y, 2) = 255;
//                }
//                else if (abs(result[image.width() * x + y]) < 0) {
//                    image(x, y, 0) = 0;
//                    image(x, y, 1) = 0;
//                    image(x, y, 2) = 0;
//                }
//                else {
//                    image(x, y, 0) = abs(result[image.width() * x + y]);
//                    image(x, y, 1) = abs(result[image.width() * x + y]);
//                    image(x, y, 2) = abs(result[image.width() * x + y]);
//                }
//
//            }
//        }
//        image.save_bmp(getOutputPath().c_str());
//	}
//	catch (CImgIOException e) {
//		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
//	}

}