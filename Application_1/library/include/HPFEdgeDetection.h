#include <string>
#include <complex>
#include <vector>
#include "CImg.h"

using namespace cimg_library;

class HPFEdgeDetection {

private:
	std::string arguments;
	std::string inputPath;
	std::string outputPath;
    std::string inputPath2;

public:
	HPFEdgeDetection(std::string arguments, std::string inputPath, std::string outputPath, std::string inputPath2);
	~HPFEdgeDetection();
	void setArguments(std::string arguments);
	std::string getArguments();
	std::string getInputPath();
	void setInputPath(std::string path);
    std::string getInputPath2();
	void setInputPath2(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
    void inverse(std::vector<std::complex<double>> matrix);
	void pass();
};