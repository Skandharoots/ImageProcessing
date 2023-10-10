#include <string>

class FlipVertical {

private:
	std::string inputPath;
	std::string outputPath;
public:
	FlipVertical(std::string inputPath, std::string outputPath);
	~FlipVertical();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void flip();
};