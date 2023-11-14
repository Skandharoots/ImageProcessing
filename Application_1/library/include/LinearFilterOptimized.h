#include <string>

class LinearFilterOptimized {

    private:
    std::string inputPath;
    std::string outputPath;
    std::string arguments;

    public:
    LinearFilterOptimized(std::string inputPath, std::string outputPath);
    ~LinearFilterOptimized();
    std::string getInputPath();
    void setInputPath(std::string path);
    std::string getOutputPath();
    void setOutputPath(std::string path);
    void setMask(int mask[]);
    void linearFilter();

};