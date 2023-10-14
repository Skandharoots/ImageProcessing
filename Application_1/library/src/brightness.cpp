#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include "CImg.h"
#include "brightness.h"

using namespace cimg_library;

Brightness::Brightness(std::string arguments, std::string input, std::string output) {
	this->arguments = arguments;
	this->input = input;
	this->output = output;
	
}

Brightness::~Brightness() {

}

void Brightness::setArguments(std::string arguments) {
	this->arguments = arguments;
}

std::string Brightness::getArguments() {
	return this->arguments;
}

std::string Brightness::getInputPath() {
	return this->input;
}

void Brightness::setInputPath(std::string path) {
	this->input = path;
}

std::string Brightness::getOutputPath() {
	return this->output;
}

void Brightness::setOutputPath(std::string path) {
	this->output = path;
}

void Brightness::setValue(int value) {
	this->value = value;
}

int Brightness::getValue() {
	return this->value;
}

void Brightness::convertArguments() {

	std::stringstream ss(getArguments());
	std::string del;
	std::vector<std::string> v;
	int temp = 0;
	const std::regex parameter1("[-](value)");
	const std::regex parameter2("[0-9]+");
	const std::regex parameter3("[-][0-9]+");
	while (getline(ss, del, '=')) {
		v.push_back(del);
	}
	if (regex_match(v[0], parameter1) == 1) {
		if (regex_match(v[1], parameter2) == 1) {
			temp = stoi(v[1]);
			setValue(temp);
		}
		else if (regex_match(v[1], parameter3)) {
			del = v[1].substr(v[1].find("-") + 1);
			temp = stoi(del) * -1;
			setValue(temp);
		}
		else {
			throw std::exception("Cannot convert argument value.\n");
		}
	}
	else {
		throw std::exception("Wrong arguments! See --help for more info.");
	}

}

float Brightness::calculate(float val) {
	if (val + getValue() > 255) {
		val = 255;
	}
	else if (val + getValue() < 0) {
		val = 0;
	}
	else {
		val += getValue();
	}
	return val;
}

void Brightness::changeBrightness() {
	try {
		convertArguments();
		CImg<unsigned char> image(getInputPath().c_str()); // create the image from a file (must exist in the working dir)
		for (int x = 0; x < image.width(); x++) {
			for (int y = 0; y < image.height(); y++) { // only upper half of the image gets processed
				float valR = image(x, y, 0); // Read red value at coordinates (x, y)
				float valG = image(x, y, 1); // Read green value at coordinates (x, y)
				float valB = image(x, y, 2); // Read blue value at coordinates (x, y)
				image(x, y, 0) = calculate(valR);
				image(x, y, 1) = calculate(valG);
				image(x, y, 2) = calculate(valB);
			}
		}
		image.save_bmp(getOutputPath().c_str()); // save the modified image to a file
	} catch (CImgIOException e) {
		throw std::exception("Cannot open or save file from path provided. Path is invalid.\n");
	} catch (std::exception& e) {
		throw std::exception(e.what());
	}
}