#pragma once

#include <string>
#include "CImg.h"

class Brightness {
private:
	std::string arguments;
	std::string input;
	std::string output;
	int value = 0;

public:
	Brightness(std::string arguments, std::string input, std::string output);
	~Brightness();
	void setArguments(std::string arguments);
	std::string getArguments();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void setValue(int value);
	int getValue();
	void convertArguments();
	void changeBrightness();
};