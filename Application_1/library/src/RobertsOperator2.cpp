#include <string>
#include "RobertsOperator2.h"
#include "CImg.h"

using namespace cimg_library;

RobertsOperator2::RobertsOperator2(std::string inputPath, std::string outputPath) {

	this->inputPath = inputPath;
	this->outputPath = outputPath;
}

RobertsOperator2::~RobertsOperator2() {
}

std::string RobertsOperator2::getInputPath() {
	return this->inputPath;
}
void RobertsOperator2::setInputPath(std::string path) {
	this->inputPath = path;
}

std::string RobertsOperator2::getOutputPath() {
	return this->outputPath;
}

void RobertsOperator2::setOutputPath(std::string path) {
	this->outputPath = path;
}

void RobertsOperator2::filter() {

	cimg::exception_mode(0);
	try {
		CImg<unsigned char> image(getInputPath().c_str());
        CImg<unsigned char> copy(getInputPath().c_str());
        for (int x = 1; x < image.width() - 1; x++) {
            for (int y = 1; y < image.height() - 1; y++) {
                for (int k = 0; k <= 2; k++) {
                    float sum = abs(copy(x, y, k) - copy(x + 1, y + 1, k)) + abs(copy(x, y + 1, k) - copy(x + 1, y, k));
					if (sum > 255) {
						image(x, y, k) = 255;
					} else if (sum < 0) {
						image(x, y, k) = 0;
					} else {
						image(x, y, k) = sum;
					}
                }
            }
        }
		image.save_bmp(getOutputPath().c_str());
	}
	catch (CImgIOException e) {
		throw std::exception("There was a problem with opening or saving a file. Path not valid.");
	} catch (std::exception &e) {
        throw std::exception(e.what());
    }
}