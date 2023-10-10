#include <string>

class FlipHorizontal {

private:
	std::string inputPath;
	std::string outputPath;
public:
	FlipHorizontal(std::string inputPath, std::string outputPath);
	~FlipHorizontal();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void flip();
};