#include <string>
#include "CImg.h"

class MaximumDifference {

private:
    std::string oryginalFile;
    std::string processedFile;
public:
    MaximumDifference(std::string oryginalFile, std::string processedFile);
    ~MaximumDifference();
    std::string getOryginalFile();
	void setOryginalFile(std::string path);
	std::string getProcessedFile();
	void setProcessedFile(std::string path);
    void calculate();
};