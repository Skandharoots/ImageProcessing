#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include "CImg.h"
#include "Shrink.h"

using namespace cimg_library;

Shrink::Shrink(std::string arguments, std::string inputPath, std::string outputPath) {
	this->arguments = arguments;
	this->input = inputPath;
	this->output = outputPath;
	
}

Shrink::~Shrink() {

}

void Shrink::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string Shrink::getArguments() {
	return this->arguments;
}

std::string Shrink::getInputPath() {
	return this->input;
}

void Shrink::setInputPath(std::string path) {
	this->input = path;
}

std::string Shrink::getOutputPath() {
	return this->output;
}

void Shrink::setOutputPath(std::string path) {
	this->output = path;
}

void Shrink::setScale(float scale) {
	this->scale = scale;
}

float Shrink::getScale() {
	return this->scale;
}

void Shrink::convertArguments() {

	std::stringstream ss(getArguments());
	std::string del;
	std::vector<std::string> v;
	float temp = 0;
	const std::regex parameter1("[-](scale)");
	const std::regex parameter2("[0-9]+(.([0-9]*))?");
	while (getline(ss, del, '=')) {
		v.push_back(del);
	}
	if (regex_match(v[0], parameter1) == 1) {
		if (regex_match(v[1], parameter2) == 1 && stof(v[1])>=1) {
			temp = stof(v[1]);
			setScale(temp);
			std::cout << getScale() << "\n";
		}
		else {
			throw std::exception("Cannot convert argument value.\n");
		}
	}
	else {
		throw std::exception("Wrong arguments! See --help for more info.");
	}

}

void Shrink::shrink() {
	cimg::exception_mode(0);
	try {
		convertArguments();
		CImg<unsigned char> image(getInputPath().c_str()); // create the image from a file (must exist in the working dir)
		int imWidth = static_cast<int>(image.width() / getScale());
        int imHeight = static_cast<int>(image.height() / getScale());
        CImg<unsigned char> shrinkedImage(imWidth, imHeight, 1, image.spectrum());
        for (int x = 0; x < imWidth; x++) {
            for (int y = 0; y < imHeight; y++) {
            int imX = static_cast<int>(x * getScale());
            int imY = static_cast<int>(y * getScale());
            for (int z = 0; z < image.spectrum(); z++) {
                shrinkedImage(x, y, z) = image(imX, imY, z);
            }
        }
    }
		shrinkedImage.save_bmp(getOutputPath().c_str()); // save the modified image to a file
	} catch (CImgIOException e) {
		throw std::exception("Cannot open or save file from path provided. Path is invalid.\n");
	} catch (std::exception& e) {
		throw std::exception(e.what());
	}
}