#include <string>
#include "CImg.h"

class M2 {
private:
	std::string arguments;
	std::string input;
	std::string output;

public:
	M2(std::string arguments, std::string input, std::string output);
	~M2();
	void setArguments(std::string arguments);
	std::string getArguments();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void setMatrix(int matrix[]);
	void operate();
};