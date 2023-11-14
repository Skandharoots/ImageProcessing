#include <string>

class LinearFilter {

    private:
    std::string inputPath;
    std::string outputPath;
    std::string arguments;

    public:
    LinearFilter(std::string arguments, std::string inputPath, std::string outputPath);
    ~LinearFilter();
    std::string getInputPath();
    void setInputPath(std::string path);
    std::string getOutputPath();
    void setOutputPath(std::string path);
    std::string getArguments();
    void setArguments(std::string path);
    void setMask(int mask[]);
    void linearFilter();

};