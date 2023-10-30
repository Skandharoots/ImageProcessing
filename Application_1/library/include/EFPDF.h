#include <string>

class EFPDF {

private:
    std::string inputPath;
    std::string outputPath;
    std::string histogramPath;
    std::string arguments;
    int gmin;
    float alpha;
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
    float getAlpha();
    void setAlpha(float alpha);
    void parseArguments();
    void efpdfCalculate();

};