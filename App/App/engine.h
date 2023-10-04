#pragma once

#include <string>

class Engine {
private:
    std::string command;
    std::string value;
    std::string inputPath;
    std::string outputPath;
public:
    Engine(std::string command, std::string value, std::string inputPath, std::string outputPath);
    ~Engine();
    void setCommand(std::string command);
    std::string getCommand();
    void setValue(std::string value);
    std::string getValue();
    void setInputPath(std::string path);
    std::string getInputPath();
    void setOutputPath(std::string path);
    std::string getOutputPath();
    int convertValue(std::string var);
    std::string convertInputPath(std::string path);
    std::string convertOutputPath(std::string path);
    void openImage();
};