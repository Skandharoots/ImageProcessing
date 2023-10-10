#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <math.h>
#include "CImg.h"
#include "contrast.h"

using namespace cimg_library;

Contrast::Contrast(std::string arguments, std::string input, std::string output) {
	this->arguments = arguments;
	this->input = input;
	this->output = output;
}

Contrast::~Contrast() {

}

void Contrast::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string Contrast::getArguments() {
	return this->arguments;
}

std::string Contrast::getInputPath() {
	return this->input;
}

void Contrast::setInputPath(std::string path) {
	this->input = path;
}

std::string Contrast::getOutputPath() {
	return this->output;
}

void Contrast::setOutputPath(std::string path) {
	this->output = path;
}

void Contrast::setSlope(float slope) {
	this->slope = slope;
}

float Contrast::getSlope() {
	return this->slope;
}

void Contrast::convertArguments() {

	std::stringstream ss(getArguments());
	std::string del;
	std::vector<std::string> v;
	float temp = 0;
	const std::regex parameter1("[-](slope)");
	const std::regex parameter2("[0-9]+(.([0-9]*))?");
	while (getline(ss, del, '=')) {
		v.push_back(del);
	}
	if (regex_match(v[0], parameter1) == 1) {
		if (regex_match(v[1], parameter2) == 1) {
			temp = stof(v[1]);
			setSlope(temp);
			std::cout << getSlope() << "\n";
		}
		else {
			throw std::exception("Cannot convert argument value.\n");
		}
	}
	else {
		throw std::exception("Wrong arguments! See --help for more info.");
	}

}

float Contrast::detectSpectrum(float value) {
	if (value > 128) {
		float temp = value - 128;
		temp *= getSlope();
		if (128 + temp > 255) {
			value = 255;
		}
		else {
			value = 128 + temp;
		}
	}
	else if (value < 128) {
		float temp = 128 - value;
		temp *= getSlope();
		if (128 - temp < 0) {
			value = 0;
		}
		else {
			value = 128 - temp;
		}
	}
	return value;
}

void Contrast::changeContrast() {
	cimg::exception_mode(0);
	try {
		convertArguments();
		CImg<unsigned char> image(getInputPath().c_str()); // create the image from a file (must exist in the working dir)
		for (int x = 0; x < image.width(); x++) {
			for (int y = 0; y < image.height(); y++) { // only upper half of the image gets processed
				for (int i = 0; i < image.spectrum(); i++) {
					image(x, y, i) = detectSpectrum(image(x, y, i));
				}
			}
		}
		image.save_bmp(getOutputPath().c_str()); // save the modified image to a file
	}
	catch (CImgIOException e) {
		throw std::exception("Cannot load or save from the path. Path invalid.\n");
	}
	catch (std::exception& e) {
		throw std::exception(e.what());
	}
	
}