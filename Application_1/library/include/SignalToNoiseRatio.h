#include <string>
#include "CImg.h"

class SignalToNoiseRatio {

private:
    std::string oryginalFile;
    std::string processedFile;
public:
    SignalToNoiseRatio(std::string oryginalFile, std::string processedFile);
    ~SignalToNoiseRatio();
    std::string getOryginalFile();
	void setOryginalFile(std::string path);
	std::string getProcessedFile();
	void setProcessedFile(std::string path);
    void calculate();
};