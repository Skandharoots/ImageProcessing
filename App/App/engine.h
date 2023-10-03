#pragma once

#include <string>

class Engine {
private:
    std::string command;
    std::string name;
    int params;
public:
    Engine();
    ~Engine();
    void setCommand(std::string command);
    std::string getCommand();
    void setName(std::string name);
    std::string getName();
    void setParams(int params);
    int getParams();
    void convertParameter(std::string var);
    void openImage();
};