#include <string>
#include "CImg.h"

class Erosion {
private:
	std::string arguments;
	std::string input;
	std::string output;

public:
	Erosion(std::string arguments, std::string input, std::string output);
	~Erosion();
	void setArguments(std::string arguments);
	std::string getArguments();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void setMatrix(int matrix[]);
	void erosion();
};