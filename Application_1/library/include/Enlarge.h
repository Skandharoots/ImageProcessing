#include <string>
#include "CImg.h"

class Enlarge {
private:
	std::string arguments;
	std::string input;
	std::string output;
	float scale = 0;

public:
	Enlarge(std::string arguments, std::string input, std::string output);
	~Enlarge();
	void setArguments(std::string arguments);
	std::string getArguments();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void setScale(float scale);
	float getScale();
	void convertArguments();
	void enlarge();
};