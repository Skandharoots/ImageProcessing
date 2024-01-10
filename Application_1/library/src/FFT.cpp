#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include "FFT.h"
#include "CImg.h"

using namespace cimg_library;

FFT::FFT(std::string inputPath, std::string outputPath) {

	this->inputPath = inputPath;
	this->outputPath = outputPath;
    
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

std::vector<std::complex<double>> FFT::forward() {
    CImg<unsigned char> image(getInputPath().c_str());
    CImg<unsigned char> magnitude(getInputPath().c_str());
    CImg<unsigned char> output(image.width(), image.height(), 1, 3);
    std::complex<double> i;
    i = -1;
    i = sqrt(i);
    std::vector<std::complex<double>> matrix;
    std::vector<std::complex<double>> matrix2;
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            float avg = (image(x, y, 0) + image(x, y, 1) + image(x, y, 2)) / 3;
            image(x, y, 0) = avg;
            image(x, y, 1) = avg;
            image(x, y, 2) = avg;

        }
    }
    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            std::complex<double> sum = 0;
            for (int yy = 0; yy < image.height(); yy++) {
                double angle =  2.0 * M_PI * y * yy / image.height();
                sum += (double)image(x, yy, 0) * (cos(angle) -i*sin(angle));
            }
            matrix.push_back(sum);
        }
    }
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            std::complex<double> sum = 0;
            for (int xx = 0; xx < image.width(); xx++) {
                double angle =  2.0 * M_PI * x * xx / image.width();
                sum += matrix[(image.width() * y) + xx] * (cos(angle) -i*sin(angle));
            }                
            matrix2.push_back(sum);
            double mag = sqrt(pow(sum.real(), 2) + pow(sum.imag(), 2));
            magnitude(x, y, 0) = 20 * log(1 + mag);
            magnitude(x, y, 1) = 20 * log(1 + mag);
            magnitude(x, y, 2) = 20 * log(1 + mag);
        }
    }
    for (int x = 0; x < image.width() / 2; x++) {
        for (int y = 0; y < image.height() / 2; y++) {
            output(x + (image.width()/2), y + (image.height()/2), 0) = magnitude(x, y, 0);
            output(x + (image.width()/2), y + (image.height()/2), 1) = magnitude(x, y, 1);
            output(x + (image.width()/2), y + (image.height()/2), 2) = magnitude(x, y, 2);
        }
    }
    for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
        for (int y = 0; y < image.height() / 2; y++) {
            output(x - (image.width()/2), y + (image.height()/2), 0) = magnitude(x, y, 0);
            output(x - (image.width()/2), y + (image.height()/2), 1) = magnitude(x, y, 1);
            output(x - (image.width()/2), y + (image.height()/2), 2) = magnitude(x, y, 2);
        }
    }
    for (int x = 0; x < image.width() / 2; x++) {
        for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
            output(x + (image.width()/2), y - (image.height()/2), 0) = magnitude(x, y, 0);
            output(x + (image.width()/2), y - (image.height()/2), 1) = magnitude(x, y, 1);
            output(x + (image.width()/2), y - (image.height()/2), 2) = magnitude(x, y, 2);
        }
    }
    for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
        for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
            output(x - (image.width()/2), y - (image.height()/2), 0) = magnitude(x, y, 0);
            output(x - (image.width()/2), y - (image.height()/2), 1) = magnitude(x, y, 1);
            output(x - (image.width()/2), y - (image.height()/2), 2) = magnitude(x, y, 2);
        }
    }
	output.save_bmp("../../../../images/fftmag.bmp");
    return matrix2;
}

void FFT::inverse(std::vector<std::complex<double>> matrix) {
    CImg<unsigned char> image(getInputPath().c_str());
    std::complex<double> i;
    i = -1;
    i = sqrt(i);
    std::vector<std::complex<double>> matrix2;
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            std::complex<double> sum = 0;
            for (int xx = 0; xx < image.width(); xx++) {
                double angle =  2.0 * M_PI * x * xx / image.width();
                sum += matrix[(image.width() * xx) + y] * (cos(angle) + i*sin(angle));
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
                double mag = sqrt(pow(sum.real(), 2) + pow(sum.imag(), 2));
                image(x, y, 0) = mag;
                image(x, y, 1) = mag;
                image(x, y, 2) = mag;
            }
        }
    image.save_bmp(getOutputPath().c_str());

}


void FFT::transform() {
	cimg::exception_mode(0);
	try {
        std::vector<std::complex<double>> matrix;
        matrix = forward();
        inverse(matrix);
	}
	catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}

}