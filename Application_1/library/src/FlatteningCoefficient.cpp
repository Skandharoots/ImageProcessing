#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "CImg.h"
#include "FlatteningCoefficient.h"

using namespace cimg_library;

FlatteningCoefficient::FlatteningCoefficient(std::string input, std::string histogram) {

    this->input = input;
    this->histogram = histogram;

}

FlatteningCoefficient::~FlatteningCoefficient() {

}

std::string FlatteningCoefficient::getInput() {
    return this->input;
}

void FlatteningCoefficient::setInput(std::string input) {
    this->input = input;
}

std::string FlatteningCoefficient::getHistogram() {
    return this->histogram;
}

void FlatteningCoefficient::setHistogram(std::string histogram) {
    this->histogram = histogram;
}

void FlatteningCoefficient::calculateFlatteningCoefficient() {

    cimg::exception_mode(0);
	try {
		CImg<unsigned char> image(getInput().c_str());
        CImg<unsigned char> histogram(getHistogram().c_str());
        int arr[256];
        int channel = -1;
        int count = 0;
        double sum = 0;
        double sum2 = 0;
        double sum3 = 0;
        double mean = 0;
        double sigma = 50;
        std::string channelS;

        for (int i = 0; i < 256; i++) {
            arr[i] = 0;
        }

        for (int i = 0; i < histogram.width(); i++) {
            for (int j = histogram.height() - 1; j >= 0; j--) {
                if((histogram(i, j, 0) == 255 && histogram(i, j, 1) == 0 && histogram(i, j, 2) == 0)) {
                    channel = 0;
                    count++;
                }
                else if((histogram(i, j, 0) == 0 && histogram(i, j, 1) == 255 && histogram(i, j, 2) == 0)) {
                    channel = 1;
                    count++;
                }
                else if ((histogram(i, j, 0) == 0 && histogram(i, j, 1) == 0 && histogram(i, j, 2) == 255)) {
                    channel = 2;
                    count++;
                }
                else {
                    channel = channel;
                }
            }
            arr[i] = count;
            count = 0;
            }
            if (channel == 0) {
            channelS = "Red";
            } else if (channel == 1) {
            channelS = "Grenn";
            } else if (channel == 2) {
            channelS = "Blue";
            }
            else {
                channelS = "No channel selected";
            }
            //Mean
            for (int i = 0; i <= 255; i++) {
                sum += i * (arr[i] * 20);
            }
            mean = sum / ((image.height() * image.width()));
            //Assymetry coefficient
            for (int i = 0; i <= 255; i++) {
                sum3 += (pow((i-mean), 4) * (arr[i] * 20));
            }
            double bk = ((1 / pow(sigma, 4)) * sum3) / (image.width() * image.height()) - 3; 
            std::cout << "Flattening coefficient` for channel(" << channelS << ") = " << std::fixed << bk << std::setprecision(10) << std::endl;

    } catch (CImgIOException e) {
		throw std::exception("There was a problem with opening or saving a file. Path not valid.");
	}


}