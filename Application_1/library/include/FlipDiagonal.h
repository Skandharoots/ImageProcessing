#include <string>

class FlipDiagonal {

private:
	std::string inputPath;
	std::string outputPath;
public:
	FlipDiagonal(std::string inputPath, std::string outputPath);
	~FlipDiagonal();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void flip();
};