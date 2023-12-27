#include <string>

class FFT {

private:
	std::string inputPath;
	std::string outputPath;
public:
	FFT(std::string inputPath, std::string outputPath);
	~FFT();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void transform();
};