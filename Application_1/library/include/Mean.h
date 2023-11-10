#include <string>

class Mean {

private:
    std::string input;
    std::string output;
    std::string histogram;

public:
    Mean(std::string input, std::string histogram);
    ~Mean();
    std::string getInput();
    void setInput(std::string input);
    std::string getHistogram();
    void setHistogram(std::string histogram);
    void calculateMean();

};

