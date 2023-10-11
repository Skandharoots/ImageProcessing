#include <string>

class GeometricMeanFilter {
private:
    std::string inputPath;
    std::string outputPath;
public:
    GeometricMeanFilter(std::string inputPath, std::string outputPath);
    ~GeometricMeanFilter();
    std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
    void filter();
};