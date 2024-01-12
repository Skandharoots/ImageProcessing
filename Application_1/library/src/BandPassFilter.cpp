#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include "BandPassFilter.h"
#include "CImg.h"
#include "FFT.h"

using namespace cimg_library;

BandPassFilter::BandPassFilter(std::string arguments, std::string inputPath, std::string outputPath) {
    this->arguments = arguments;
	this->inputPath = inputPath;
	this->outputPath = outputPath;
	
}

void BandPassFilter::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string BandPassFilter::getArguments() {
	return this->arguments;
}

BandPassFilter::~BandPassFilter() {
}

std::string BandPassFilter::getInputPath() {
	return this->inputPath;
}
void BandPassFilter::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string BandPassFilter::getOutputPath() {
	return this->outputPath;
}

void BandPassFilter::setOutputPath(std::string path) {
	this->outputPath = path;
}

void BandPassFilter::inverse(std::vector<std::complex<double>> matrix) {
    CImg<unsigned char> image(getInputPath().c_str());
    std::complex<double> i;
    i = -1;
    i = sqrt(i);
    std::vector<std::complex<double>> matrix2;
    std::vector<std::complex<double>> transformOutput(image.width() * image.height(), 0.0);

    for (int x = 0; x < image.width() / 2; x++) {
        for (int y = 0; y < image.height() / 2; y++) {
            transformOutput[(x + (image.width()/2)) + (y + image.height()/2) * image.width()] = matrix[image.width() * y + x];
        }
    }
    for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
        for (int y = 0; y < image.height() / 2; y++) {
            transformOutput[(x - (image.width()/2)) + (y + image.height()/2) * image.width()] = matrix[image.width() * y + x];
        }
    }
    for (int x = 0; x < image.width() / 2; x++) {
        for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
            transformOutput[(x + (image.width()/2)) + (y - image.height()/2) * image.width()] = matrix[image.width() * y + x];
        }
    }
    for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
        for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
            transformOutput[(x - (image.width()/2)) + (y - image.height()/2) * image.width()] = matrix[image.width() * y + x];
        }
    }

    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            std::complex<double> sum = 0;
            for (int xx = 0; xx < image.width(); xx++) {
                double angle =  2.0 * M_PI * x * xx / image.width();
                sum += transformOutput[(image.width() * xx) + y] * (cos(angle) + i*sin(angle));
            }
            sum = sum / (double)image.width();
            matrix2.push_back(sum);
        }
    }
    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            std::complex<double> sum = 0;
            for (int yy = 0; yy < image.height(); yy++) {
                double angle =  2.0 * M_PI * y * yy / image.height();
                sum += matrix2[(image.width() * x) + yy] * (cos(angle) + i*sin(angle));
            }
            sum = sum / (double)image.height();
            double pls = sum.real();
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

void BandPassFilter::pass() {
	cimg::exception_mode(0);
	try {
        CImg<unsigned char> image(getInputPath().c_str());

        FFT fft(getInputPath().c_str(), getOutputPath().c_str());
        CImg<unsigned char> magnitude(getInputPath().c_str());


        std::vector<std::complex<double>> transformOutput;
        std::vector<std::complex<double>> filterBandPass(image.width() * image.height(), 0.0);

        std::string cutoffFrequencies = getArguments();
        auto space = cutoffFrequencies.find(' ');
        double lowCut = stod(cutoffFrequencies.substr(0, space));
        double highCut = stod(cutoffFrequencies.substr(space + 1));

        double radialCenter = (lowCut + highCut) / 2;
        double bandWidth = highCut - lowCut;

        for (int y = 0; y < image.height(); y++) {
            for (int x = 0; x < image.width(); x++) {
                int index = y * image.width() + x;
                int xx = abs(image.width()/2 - x);
                int yy = abs(image.height()/2 - y);
                if(sqrt(xx * xx + yy * yy) >= (radialCenter - (bandWidth / 2))
                && sqrt(xx * xx + yy * yy) <= (radialCenter + (bandWidth / 2))) {
                    filterBandPass[index] = 1;
                }
            }
        }

        transformOutput = fft.forward();

        for (int i = 0; i < transformOutput.size(); i++) {
            transformOutput[i] *= filterBandPass[i];
        }
        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double mag = sqrt(pow(transformOutput[image.width() * y + x].real(), 2) + pow(transformOutput[image.width() * y + x].imag(), 2));
                magnitude(x, y, 0) = 20 * log(1 + mag);
                magnitude(x, y, 1) = 20 * log(1 + mag);
                magnitude(x, y, 2) = 20 * log(1 + mag);
            }
        }

        magnitude.save_bmp("../../../../images/bpfmag.bmp");

        inverse(transformOutput);
	}
	catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}

}