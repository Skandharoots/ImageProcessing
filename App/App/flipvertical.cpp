#include <string>
#include "flipvertical.h"
#include "CImg.h"

using namespace cimg_library;

FlipVertical::FlipVertical(std::string inputPath, std::string outputPath) {

	this->inputPath = inputPath;
	this->outputPath = outputPath;
}

FlipVertical::~FlipVertical() {
}

std::string FlipVertical::getInputPath() {
	return this->inputPath;
}
void FlipVertical::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string FlipVertical::getOutputPath() {
	return this->outputPath;
}

void FlipVertical::setOutputPath(std::string path) {
	this->outputPath = path;
}

void FlipVertical::flip() {

	cimg::exception_mode(0);
	try {
		CImg<unsigned char> image(getInputPath().c_str());
		//CImg<unsigned char> copy(image.width(), image.height(), 1, 3);
		float temp0 = 0;
		float temp1 = 0;
		float temp2 = 0;
		if (image.spectrum() == 1) {
			for (int x = 0; x < image.width()/2; x++) {
				for (int y = 0; y < image.height(); y++) {
					temp0 = image(x, y, 0);
					image(x, y, 0) = image(image.width() - x - 1, y, 0);
					image(image.width() - x - 1, y, 0) = temp0;
				}
			}
		}
		if (image.spectrum() == 3) {
			for (int x = 0; x < image.width()/2; x++) {
				for (int y = 0; y < image.height(); y++) {
					temp0 = image(x, y, 0);
					temp1 = image(x, y, 1);
					temp2 = image(x, y, 2);
					image(x, y, 0) = image(image.width() - x - 1, y, 0);
					image(image.width() - x - 1, y, 0) = temp0;
					image(x, y, 1) = image(image.width() - x - 1, y, 1);
					image(image.width() - x - 1, y, 1) = temp1;
					image(x, y, 2) = image(image.width() - x - 1, y, 2);
					image(image.width() - x - 1, y, 2) = temp2;
				}
			}
		}
		image.save_bmp(getOutputPath().c_str());
	}
	catch (CImgIOException e) {
		throw std::exception("Cannot load or save from the path. Path invalid.\n");
	}
}