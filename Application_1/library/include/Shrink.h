#include <string>
#include "CImg.h"

class Shrink {
private:
	std::string arguments;
	std::string input;
	std::string output;
	float scale = 0;

public:
	Shrink(std::string arguments, std::string input, std::string output);
	~Shrink();
	void setArguments(std::string arguments);
	std::string getArguments();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void setScale(float scale);
	float getScale();
	void convertArguments();
	void shrink();
};