#include <string>
#include <complex>
#include <vector>
#include "CImg.h"

using namespace cimg_library;

class FFT {

private:
	std::string inputPath;
	std::string outputPath;
	std::string outputPath2;
public:
	FFT(std::string inputPath, std::string outputPath);
	~FFT();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	std::vector<std::complex<double>> forward();
	void inverse(std::vector<std::complex<double>> matrix);
	void transform();
};