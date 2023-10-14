#include <string>
#include "CImg.h"

class PeakMeanSquareError {

private:
    std::string oryginalFile;
    std::string processedFile;
public:
    PeakMeanSquareError(std::string oryginalFile, std::string processedFile);
    ~PeakMeanSquareError();
    std::string getOryginalFile();
	void setOryginalFile(std::string path);
	std::string getProcessedFile();
	void setProcessedFile(std::string path);
    void calculate();
};