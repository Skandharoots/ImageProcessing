#include <string>

class InfSourceEntropy {

private:
    std::string input;
    std::string histogram;

public:
    InfSourceEntropy(std::string input, std::string histogram);
    ~InfSourceEntropy();
    std::string getInput();
    void setInput(std::string input);
    std::string getHistogram();
    void setHistogram(std::string histogram);
    void calculateInfSourceEntropy();

};