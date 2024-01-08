#include <string>
#include <complex>
#include <vector>
#include "CImg.h"

using namespace cimg_library;

class HighPassFilter {

private:
	std::string arguments;
	std::string inputPath;
	std::string outputPath;

public:
	HighPassFilter(std::string arguments, std::string inputPath, std::string outputPath);
	~HighPassFilter();
	void setArguments(std::string arguments);
	std::string getArguments();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void pass();
};