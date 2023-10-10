#include <string>
#include "fliphorizontal.h"
#include "CImg.h"

using namespace cimg_library;

FlipHorizontal::FlipHorizontal(std::string inputPath, std::string outputPath) {

	this->inputPath = inputPath;
	this->outputPath = outputPath;
}

FlipHorizontal::~FlipHorizontal() {
}

std::string FlipHorizontal::getInputPath() {
	return this->inputPath;
}
void FlipHorizontal::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string FlipHorizontal::getOutputPath() {
	return this->outputPath;
}

void FlipHorizontal::setOutputPath(std::string path) {
	this->outputPath = path;
}

void FlipHorizontal::flip() {

	cimg::exception_mode(0);
	try {
		CImg<unsigned char> image(getInputPath().c_str());
		//CImg<unsigned char> copy(image.width(), image.height(), 1, 3);
		float temp0 = 0;
		float temp1 = 0;
		float temp2 = 0;
		if (image.spectrum() == 1) {
			for (int x = 0; x < image.width(); x++) {
				for (int y = 0; y < image.height() / 2; y++) {
					temp0 = image(x, y, 0);
					image(x, y, 0) = image(x, image.height() - y - 1, 0);
					image(x, image.height() - y - 1, 0) = temp0;
				}
			}
		}
		if (image.spectrum() == 3) {
			for (int x = 0; x < image.width(); x++) {
				for (int y = 0; y < image.height() / 2; y++) {
					temp0 = image(x, y, 0);
					temp1 = image(x, y, 1);
					temp2 = image(x, y, 2);
					image(x, y, 0) = image(x, image.height() - y - 1, 0);
					image(x, image.height() - y - 1, 0) = temp0;
					image(x, y, 1) = image(x, image.height() - y - 1, 1);
					image(x, image.height() - y - 1, 1) = temp1;
					image(x, y, 2) = image(x, image.height() - y - 1, 2);
					image(x, image.height() - y - 1, 2) = temp2;
				}
			}
		}
		image.save_bmp(getOutputPath().c_str());
	}
	catch (CImgIOException e) {
		throw std::exception("Cannot load or save from the path. Path invalid.\n");
	}
}