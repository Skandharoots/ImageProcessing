#include <string>

class FFT {

private:
	std::string inputPath;
	std::string outputPath;
	std::string outputPath2;
public:
	FFT(std::string inputPath, std::string outputPath, std::string outputPath2);
	~FFT();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	std::string getOutputPath2();
	void setOutputPath2(std::string path);
	void transform();
};