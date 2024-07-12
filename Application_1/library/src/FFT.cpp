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
    std::complex<double> i;
    i = -1;
    i = sqrt(i);
    std::vector<std::complex<double>> matrix;
    std::vector<std::complex<double>> matrix2;
    std::vector<std::complex<double>> transformCentered(image.width() * image.height(), 0.0);
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
        }
    }

    for (int x = 0; x < image.width() / 2; x++) {
        for (int y = 0; y < image.height() / 2; y++) {
            transformCentered[(x + (image.width()/2)) + (y + image.height()/2) * image.width()] = matrix2[image.width() * y + x];
        }
    }
    for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
        for (int y = 0; y < image.height() / 2; y++) {
            transformCentered[(x - (image.width()/2)) + (y + image.height()/2) * image.width()] = matrix2[image.width() * y + x];
        }
    }
    for (int x = 0; x < image.width() / 2; x++) {
        for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
            transformCentered[(x + (image.width()/2)) + (y - image.height()/2) * image.width()] = matrix2[image.width() * y + x];
        }
    }
    for (int x = image.width() - 1; x > image.width() / 2 - 1; x--) {
        for (int y = image.height() - 1; y > image.height() / 2 - 1; y--) {
            transformCentered[(x - (image.width()/2)) + (y - image.height()/2) * image.width()] = matrix2[image.width() * y + x];
        }
    }

    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            double mag = sqrt(pow(transformCentered[image.width() * y + x].real(), 2) + pow(transformCentered[image.width() * y + x].imag(), 2));
            if (20 * log(1 + mag) < 0) {
                magnitude(x, y, 0) = 0;
                magnitude(x, y, 1) = 0;
                magnitude(x, y, 2) = 0;
            } else if (20 * log(1 + mag) > 255) {
                magnitude(x, y, 0) = 255;
                magnitude(x, y, 1) = 255;
                magnitude(x, y, 2) = 255;
            } else {
                magnitude(x, y, 0) = 20 * log(1 + mag);
                magnitude(x, y, 1) = 20 * log(1 + mag);
                magnitude(x, y, 2) = 20 * log(1 + mag);
            }
        }
    }
	magnitude.save_bmp("../../../images/ffftmag.bmp");
    return transformCentered;
}

std::vector<std::complex<double>> FFT::inverse(std::vector<std::complex<double>> matrix) {
    CImg<unsigned char> image(getInputPath().c_str());
    std::complex<double> i;
    i = -1;
    i = sqrt(i);
    std::vector<std::complex<double>> matrix2;
    std::vector<std::complex<double>> matrix3;
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
                matrix3.push_back(sum);

            }
        }
    //image.save_bmp(getOutputPath().c_str());
    return matrix3;
}


void FFT::transform() {
	cimg::exception_mode(0);
    CImg<unsigned char> image(getInputPath().c_str());
	try {
        std::vector<std::complex<double>> matrix;
        std::vector<std::complex<double>> matrix2;
        matrix = forward();
        matrix2 = inverse(matrix);
        for (int x = 0; x < image.width(); x++) {
            for (int y = 0; y < image.height(); y++) {
                double mag = sqrt(pow(matrix2[image.width() * y + x].real(), 2) + pow(matrix2[image.width() * y + x].imag(), 2));
                image(x, y, 0) = mag;
                image(x, y, 1) = mag;
                image(x, y, 2) = mag;
            }
        }
	}
	catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}

}