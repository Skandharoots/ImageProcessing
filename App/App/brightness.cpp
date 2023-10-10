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

float Brightness::detectSpectrum(float value) {
	if (value + getValue() > 255) {
		value = 255;
	}
	else if (value + getValue() < 0) {
		value = 0;
	}
	else {
		value += getValue();
	}
	return value;
}

void Brightness::changeBrightness() {
	cimg::exception_mode(0);
	try {
		convertArguments();
		CImg<unsigned char> image(getInputPath().c_str());
		std::cout << "Spectrum: " << image.spectrum();
		for (int x = 0; x < image.width(); x++) {
			for (int y = 0; y < image.height(); y++) {
				for (int i = 0; i < image.spectrum(); i++) {
					image(x, y, i) = detectSpectrum(image(x, y, i));
				}
			}
		}
		image.save_bmp(getOutputPath().c_str());
	} catch (CImgIOException e) {
		throw std::exception("Cannot open or save file from path provided. Path is invalid.\n");
	} catch (std::exception& e) {
		throw std::exception(e.what());
	}
}