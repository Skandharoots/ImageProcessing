#include <string>

class EFPDF {

private:
    std::string inputPath;
    std::string outputPath;
    std::string histogramPath;
    std::string arguments;
    double gmin;
    int alpha;
public:
    EFPDF(std::string arguments, std::string inputPath, std::string outputPath, std::string histogramPath);
    ~EFPDF();
    std::string getInput();
    void setInput(std::string path);
    std::string getOutput();
    void setOutput(std::string path);
    std::string getHistogram();
    void setHistogram(std::string path);
    std::string getArguments();
    void setArguments(std::string arguments);
    double getGMIN();
    void setGMIN(double gmin);
    int getAlpha();
    void setAlpha(int alpha);
    void parseArguments();
    void efpdfCalculate();

};