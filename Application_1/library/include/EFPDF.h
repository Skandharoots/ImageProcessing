#include <string>

class EFPDF {

private:
    std::string inputPath;
    std::string outputPath;
    std::string histogramPath;
    std::string arguments;
    int gmin;
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
    int getGMIN();
    void setGMIN(int gmin);
    int getAlpha();
    void setAlpha(int alpha);
    void parseArguments();
    void efpdfCalculate();

};