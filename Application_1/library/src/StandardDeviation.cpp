#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "CImg.h"
#include "StandardDeviation.h"

using namespace cimg_library;

StandardDeviation::StandardDeviation(std::string input, std::string histogram) {

    this->input = input;
    this->histogram = histogram;

}

StandardDeviation::~StandardDeviation() {

}

std::string StandardDeviation::getInput() {
    return this->input;
}

void StandardDeviation::setInput(std::string input) {
    this->input = input;
}

std::string StandardDeviation::getHistogram() {
    return this->histogram;
}

void StandardDeviation::setHistogram(std::string histogram) {
    this->histogram = histogram;
}

void StandardDeviation::calculateStandardDeviation() {

    cimg::exception_mode(0);
	try {
		CImg<unsigned char> image(getInput().c_str());
        CImg<unsigned char> histogram(getHistogram().c_str());
        int arr[256];
        int channel = -1;
        int count = 0;
        double sum = 0;
        double sum2 = 0;
        double mean = 0;
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

            for (int i = 0; i <= 255; i++) {
                sum += i * (arr[i] * 20);
            }
            mean = sum / ((image.height() * image.width()));
            for (int i = 0; i <= 255; i++) {
                sum2 += pow((i - mean), 2) * (arr[i] * 20);
            }
            double std = sqrt(sum2 / (image.width() * image.height()));
            std::cout << "Standard deviation for channel(" << channelS << ") = " << std::fixed << std << std::setprecision(10) << std::endl;

    } catch (CImgIOException e) {
		throw std::exception("There was a problem with opening or saving a file. Path not valid.");
	}


}