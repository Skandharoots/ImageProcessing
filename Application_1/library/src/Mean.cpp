#include <string>
#include <iostream>
#include <iomanip>
#include "CImg.h"
#include "Mean.h"

using namespace cimg_library;

Mean::Mean(std::string input, std::string histogram) {

    this->input = input;
    this->histogram = histogram;

}

Mean::~Mean() {

}

std::string Mean::getInput() {
    return this->input;
}

void Mean::setInput(std::string input) {
    this->input = input;
}

std::string Mean::getHistogram() {
    return this->histogram;
}

void Mean::setHistogram(std::string histogram) {
    this->histogram = histogram;
}

void Mean::calculateMean() {

    cimg::exception_mode(0);
	try {
		CImg<unsigned char> image(getInput().c_str());
        CImg<unsigned char> histogram(getHistogram().c_str());
        int arr[256];
        int channel = -1;
        int count = 0;
        double sum = 0;
        double mean = 0;

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
                sum += i * arr[i] * 20;
            }
            std::cout << "Sum = " << std::fixed << sum << std::setprecision(10) << std::endl;
            mean = sum / ((image.height() * image.width()));
            std::cout << "Mean = " << std::fixed << mean << std::setprecision(10) << std::endl;

    } catch (CImgIOException e) {
		throw std::exception("There was a problem with opening or saving a file. Path not valid.");
	}


}