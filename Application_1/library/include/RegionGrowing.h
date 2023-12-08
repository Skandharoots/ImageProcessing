#include <string>
#include "CImg.h"

class RG {
private:
	std::string arguments;
	std::string input;
	std::string output;

public:
	RG(std::string arguments, std::string input, std::string output);
	~RG();
	void setArguments(std::string arguments);
	std::string getArguments();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void regionGrowing();
};