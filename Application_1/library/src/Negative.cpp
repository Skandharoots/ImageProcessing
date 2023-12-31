#include <string>
#include <stdexcept>
#include "negative.h"
#include "CImg.h"

using namespace cimg_library;

Negative::Negative(std::string input, std::string output) {

	this->input = input;
	this->output = output;
}

Negative::~Negative() {
}

std::string Negative::getInputPath() {
	return this->input;
}
void Negative::setInputPath(std::string path) {
	this->input = path;
}

std::string Negative::getOutputPath() {
	return this->output;
}

void Negative::setOutputPath(std::string path) {
	this->output = path;
}

void Negative::negate() {

	cimg::exception_mode(0);
	try {
		CImg<unsigned char> image(getInputPath().c_str());
		//CImg<unsigned char> copy(image.width(), image.height(), 1, 3);
		float temp0 = 0;
		float temp1 = 0;
		float temp2 = 0;
		if (image.spectrum() == 1) {
			for (int x = 0; x < image.width(); x++) {
				for (int y = 0; y < image.height(); y++) {
					image(x, y, 0) = 255 - image(x, y, 0);
				}
			}
		}
		else if (image.spectrum() == 3) {
			for (int x = 0; x < image.width(); x++) {
				for (int y = 0; y < image.height(); y++) {
					image(x, y, 0) = 255 - image(x, y, 0);
                    image(x, y, 1) = 255 - image(x, y, 1);
                    image(x, y, 2) = 255 - image(x, y, 2);
				}
			}
		}
		image.save_bmp(getOutputPath().c_str());
	}
	catch (CImgIOException e) {
		throw std::logic_error("Cannot load or save from the path. Path invalid.\n");
	}
}