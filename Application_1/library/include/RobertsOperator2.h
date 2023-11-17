#include <string>

class RobertsOperator2 {

private:
	std::string inputPath;
	std::string outputPath;
public:
	RobertsOperator2(std::string inputPath, std::string outputPath);
	~RobertsOperator2();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void filter();
};