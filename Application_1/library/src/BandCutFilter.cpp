#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include "BandCutFilter.h"
#include "CImg.h"
#include "FastFourierTransform.h"

using namespace cimg_library;

BandCutFilter::BandCutFilter(std::string arguments, std::string inputPath, std::string outputPath) {
    this->arguments = arguments;
	this->inputPath = inputPath;
	this->outputPath = outputPath;

}

void BandCutFilter::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string BandCutFilter::getArguments() {
	return this->arguments;
}

BandCutFilter::~BandCutFilter() {
}

std::string BandCutFilter::getInputPath() {
	return this->inputPath;
}
void BandCutFilter::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string BandCutFilter::getOutputPath() {
	return this->outputPath;
}

void BandCutFilter::setOutputPath(std::string path) {
	this->outputPath = path;
}

void BandCutFilter::pass() {
//	cimg::exception_mode(0);
//	try {
//        CImg<unsigned char> image(getInputPath().c_str());
//        CImg<unsigned char> magnitude(getInputPath().c_str());
//        CImg<unsigned char> mag(getInputPath().c_str());
//
//
//        FastFourierTransform fft(getInputPath().c_str(), getOutputPath().c_str());
//        std::vector<std::complex<double>> matrix;
//        std::vector<std::complex<double>> transformOutput;
//        std::vector<std::complex<double>> transformCentered;
//        std::vector<std::complex<double>> resultDecentered;
//        std::vector<std::complex<double>> result;
//        std::vector<std::complex<double>> filterBandCut(image.width() * image.height(), 0.0);
//
//        std::string cutoffFrequencies = getArguments();
//        auto space = cutoffFrequencies.find(' ');
//        double lowCut = stod(cutoffFrequencies.substr(0, space));
//        double highCut = stod(cutoffFrequencies.substr(space + 1));
//
//        double radialCenter = (lowCut + highCut) / 2;
//        double bandWidth = highCut - lowCut;
//
//        for (int y = 0; y < image.height(); y++) {
//            for (int x = 0; x < image.width(); x++) {
//                int index = y * image.width() + x;
//                int xx = abs(image.width()/2 - x);
//                int yy = abs(image.height()/2 - y);
//                if(sqrt(xx * xx + yy * yy) <= (radialCenter - (bandWidth / 2))
//                || sqrt(xx * xx + yy * yy) >= (radialCenter + (bandWidth / 2))) {
//                    filterBandCut[index] = 1;
//                }
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
//        for (int i = 0; i < transformOutput.size(); i++) {
//            transformCentered[i] *= filterBandCut[i];
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
//        magnitude.save_bmp("../../../../images/bcfmag.bmp");
//        resultDecentered = fft.center(transformCentered);
//        result = fft.ifft(resultDecentered);
//
//        for (int x = 0; x < image.width(); x++) {
//            for (int y = 0; y < image.height(); y++) {
//                result[image.width() * x + y] = result[image.width() * x + y] / ((double) result.size());
//                double mag = sqrt(pow(result[image.width() * x + y].real(), 2) + pow(result[image.width() * x + y].imag(), 2));
//                image(x, y, 0) = mag;
//                image(x, y, 1) = mag;
//                image(x, y, 2) = mag;
//            }
//        }
//        image.save_bmp(getOutputPath().c_str());
//	}
//	catch (CImgIOException e) {
//		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
//	}

}