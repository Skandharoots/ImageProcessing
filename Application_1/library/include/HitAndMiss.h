#include <string>
#include "CImg.h"

class HitAndMiss {
private:
	std::string arguments;
	std::string input;
	std::string output;

public:
	HitAndMiss(std::string arguments, std::string input, std::string output);
	~HitAndMiss();
	void setArguments(std::string arguments);
	std::string getArguments();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void setMatrix(int matrix[]);
	void ham();
};