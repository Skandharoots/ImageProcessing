#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "CImg.h"
#include "InformationSourceEntropy.h"

using namespace cimg_library;

InfSourceEntropy::InfSourceEntropy(std::string input, std::string histogram) {

    this->input = input;
    this->histogram = histogram;

}

InfSourceEntropy::~InfSourceEntropy() {

}

std::string InfSourceEntropy::getInput() {
    return this->input;
}

void InfSourceEntropy::setInput(std::string input) {
    this->input = input;
}

std::string InfSourceEntropy::getHistogram() {
    return this->histogram;
}

void InfSourceEntropy::setHistogram(std::string histogram) {
    this->histogram = histogram;
}

void InfSourceEntropy::calculateInfSourceEntropy() {

    cimg::exception_mode(0);
	try {
		CImg<unsigned char> image(getInput().c_str());
        CImg<unsigned char> histogram(getHistogram().c_str());
        float arr[256];
        int channel = -1;
        int count = 0;
        long double sum = 0;
        double ise = 0;
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
            if (arr[i] != 0) {
                sum += (arr[i] * 20)*(log2((arr[i] * 20) / (image.height() * image.width())));
            }
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
        ise = -1 * sum / (image.height() * image.width());
        std::cout << "Information Source Entropy for channel (" << channelS << ") = " << std::fixed << ise << std::setprecision(10) << std::endl;

    } catch (CImgIOException e) {
		throw std::logic_error("There was a problem with opening or saving a file. Path not valid.");
	}


}