#include <string>
#include "CImg.h"

class PeakSignalToNoiseRatio {

private:
    std::string oryginalFile;
    std::string processedFile;
public:
    PeakSignalToNoiseRatio(std::string oryginalFile, std::string processedFile);
    ~PeakSignalToNoiseRatio();
    std::string getOryginalFile();
	void setOryginalFile(std::string path);
	std::string getProcessedFile();
	void setProcessedFile(std::string path);
    void calculate();
};