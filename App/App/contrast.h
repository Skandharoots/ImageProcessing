#pragma once

#include <string>
#include "CImg.h"

class Contrast {
private:
	std::string arguments;
	std::string input;
	std::string output;
	float slope = 0;

public:
	Contrast(std::string arguments, std::string input, std::string output);
	~Contrast();
	void setArguments(std::string arguments);
	std::string getArguments();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void setSlope(float slope);
	float getSlope();
	void convertArguments();
	float detectSpectrum(float value);
	void changeContrast();
};
