#define _USE_MATH_DEFINES

#include <string>
#include <cmath>
#include <complex>
#include <math.h>
#include <vector>
#include <iostream>
#include "SFT.h"
#include "CImg.h"

using namespace cimg_library;

SFT::SFT(std::string inputPath, std::string outputPath) {

	this->inputPath = inputPath;
	this->outputPath = outputPath;
}

SFT::~SFT() {
}

std::string SFT::getInputPath() {
	return this->inputPath;
}
void SFT::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string SFT::getOutputPath() {
	return this->outputPath;
}

void SFT::setOutputPath(std::string path) {
	this->outputPath = path;
}

void SFT::transform() {

	cimg::exception_mode(0);
	try {
		CImg<unsigned char> image(getInputPath().c_str());
        CImg<unsigned char> magnitude(getInputPath().c_str());
        CImg<unsigned char> output(image.width(), image.height(), 1, 3);

        std::complex<double> i;
        i = -1;
        i = sqrt(i);

        std::vector<std::complex<double>> matrix;
        std::vector<double> phase;

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                output(x, y, 0) = 0;
                output(x, y, 1) = 0;
                output(x, y, 2) = 0;
            }
        }

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                std::complex<double> sum = 0;
                double ph;
                for (int ii = 0; ii < image.width(); ii++) {
                    for (int j = 0; j < image.height(); j++) {
                        double angle = 2 * M_PI * ((double)(x * ii) / (double)image.width() + (double)(y * j) / image.height());
                        sum += (double)image(ii, j, 0) * (cos(angle) - i*sin(angle));
                    }
                }
                ph = atan(sum.imag() / sum.real());
                matrix.push_back(sum);
                phase.push_back(ph);
                //std::cout << sqrt(pow(matrix[(x * y) + y].real(), 2) + pow(matrix[(x * y) + y].imag(), 2)) << std::endl;
                magnitude(x, y, 0) = sqrt(pow(matrix[(x * y) + y].real(), 2) + pow(matrix[(x * y) + y].imag(), 2));
                magnitude(x, y, 1) = sqrt(pow(matrix[(x * y) + y].real(), 2) + pow(matrix[(x * y) + y].imag(), 2));
                magnitude(x, y, 2) = sqrt(pow(matrix[(x * y) + y].real(), 2) + pow(matrix[(x * y) + y].imag(), 2));
            }
        }

        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                std::complex<double> sum = 0;
                for (int ii = 0; ii < image.width(); ii++) {
                    for (int j = 0; j < image.height(); j++) {
                        double angle = 2 * M_PI * ((double)(x * ii) / (double)image.width() + (double)(y * j) / image.height());
                        sum += matrix[((ii * j) + j)] * (cos(angle) + i*sin(angle));
                    }
                }
                sum = sum / (double)(image.width() * image.height());
                //std::cout << sqrt(pow(sum.real(), 2) + pow(sum.imag(), 2)) << std::endl;
                output(x, y, 0) = sqrt(pow(sum.real(), 2) + pow(sum.imag(), 2));
                output(x, y, 1) = sqrt(pow(sum.real(), 2) + pow(sum.imag(), 2));
                output(x, y, 2) = sqrt(pow(sum.real(), 2) + pow(sum.imag(), 2));
                sum = 0;
            }
        }

        // for (int x = 0; x < image.width() / 2; x++) {
        //     for (int y = 0; y < image.height() / 2; y++) {
        //         output(x + (image.width()/2), y + (image.height()/2), 0) = magnitude(x, y, 0);
        //         output(x + (image.width()/2), y + (image.height()/2), 1) = magnitude(x, y, 1);
        //         output(x + (image.width()/2), y + (image.height()/2), 2) = magnitude(x, y, 2);
        //     }
        // }
        // for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
        //     for (int y = 0; y < image.height() / 2; y++) {
        //         output(x - (image.width()/2), y + (image.height()/2), 0) = magnitude(x, y, 0);
        //         output(x - (image.width()/2), y + (image.height()/2), 1) = magnitude(x, y, 1);
        //         output(x - (image.width()/2), y + (image.height()/2), 2) = magnitude(x, y, 2);
        //     }
        // }
        // for (int x = 0; x < image.width() / 2; x++) {
        //     for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
        //         output(x + (image.width()/2), y - (image.height()/2), 0) = magnitude(x, y, 0);
        //         output(x + (image.width()/2), y - (image.height()/2), 1) = magnitude(x, y, 1);
        //         output(x + (image.width()/2), y - (image.height()/2), 2) = magnitude(x, y, 2);
        //     }
        // }
        // for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
        //     for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
        //         output(x - (image.width()/2), y - (image.height()/2), 0) = magnitude(x, y, 0);
        //         output(x - (image.width()/2), y - (image.height()/2), 1) = magnitude(x, y, 1);
        //         output(x - (image.width()/2), y - (image.height()/2), 2) = magnitude(x, y, 2);
        //     }
        // }
        CImgDisplay main_disp(output,"Magnitude DFT");
        while (!main_disp.is_closed()) {
            main_disp.wait();
        }
	}
	catch (CImgIOException e) {
		throw std::exception("Cannot load or save from the path. Path invalid.\n");
	}
}