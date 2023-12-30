#include <string>

class SFT {

private:
	std::string inputPath;
	std::string outputPath;
public:
	SFT(std::string inputPath, std::string outputPath);
	~SFT();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void transform();
};