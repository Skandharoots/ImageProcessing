#include <string>
#include "brightness.h"

class Engine {
private:
    std::string command;
    std::string value;
    std::string inputPath;
    std::string outputPath;
    std::string inputPath2;
public:
    Engine(std::string command, std::string value, std::string inputPath, std::string outputPath, std::string inputPath2);
    ~Engine();
    void setCommand(std::string command);
    std::string getCommand();
    void setValue(std::string value);
    std::string getValue();
    void setInputPath(std::string path);
    std::string getInputPath();
    void setOutputPath(std::string path);
    std::string getOutputPath();
    void setInputPath2(std::string path);
    std::string getInputPath2();
    //int convertValue(std::string var);
    std::string convertInputPath(std::string path);
    //std::string convertOutputPath(std::string path);
    void openImage();
};