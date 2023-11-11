#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "CImg.h"
#include "VariationCoefficient2.h"

using namespace cimg_library;

VariationCoefficient2::VariationCoefficient2(std::string input, std::string histogram) {

    this->input = input;
    this->histogram = histogram;

}

VariationCoefficient2::~VariationCoefficient2() {

}

std::string VariationCoefficient2::getInput() {
    return this->input;
}

void VariationCoefficient2::setInput(std::string input) {
    this->input = input;
}

std::string VariationCoefficient2::getHistogram() {
    return this->histogram;
}

void VariationCoefficient2::setHistogram(std::string histogram) {
    this->histogram = histogram;
}

void VariationCoefficient2::calculateVariationCoefficient2() {

    cimg::exception_mode(0);
	try {
		CImg<unsigned char> image(getInput().c_str());
        CImg<unsigned char> histogram(getHistogram().c_str());
        int arr[256];
        int channel = -1;
        int count = 0;
        double sum = 0;
        double vc2 = 0;
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

        for (int i = 0; i <= 255; i++) {
            sum += pow(arr[i] * 20, 2);
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
        vc2 = sum / (pow((image.height() * image.width()), 2));
        std::cout << "Variation Coefficient II for channel (" << channelS << ") = " << std::fixed << vc2 << std::setprecision(10) << std::endl;

    } catch (CImgIOException e) {
		throw std::exception("There was a problem with opening or saving a file. Path not valid.");
	}


}