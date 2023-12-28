#include <string>

class IFFT {

private:
	std::string inputPath;
	std::string outputPath;
	std::string inputPath2;
public:
	IFFT(std::string inputPath, std::string outputPath, std::string inputPath2);
	~IFFT();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	std::string getInputPath2();
	void setInputPath2(std::string path);
	void transform();
};