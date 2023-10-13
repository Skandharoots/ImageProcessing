
#include <string>
#include "CImg.h"

class MeanSquareError {

private:
    std::string oryginalFile;
    std::string processedFile;
public:
    MeanSquareError(std::string oryginalFile, std::string processedFile);
    ~MeanSquareError();
    std::string getOryginalFile();
	void setOryginalFile(std::string path);
	std::string getProcessedFile();
	void setProcessedFile(std::string path);
    void calculate();
};