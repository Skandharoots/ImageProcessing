#include <string>

class IFFT {

private:
	std::string inputPath;
	std::string outputPath;
public:
	IFFT(std::string inputPath, std::string outputPath);
	~IFFT();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void transform();
};