#pragma once

#include <string>

class Engine {
private:
    std::string command;
    std::string name;
    std::string params;
public:
    Engine();
    ~Engine();
    void setCommand(std::string command);
    std::string getCommand();
    void setName(std::string name);
    std::string getName();
    void setParams(std::string params);
    std::string getParams();
    void openImage();
};