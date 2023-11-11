#include <string>

class Variance {

private:
    std::string input;
    std::string output;
    std::string histogram;

public:
    Variance(std::string input, std::string histogram);
    ~Variance();
    std::string getInput();
    void setInput(std::string input);
    std::string getHistogram();
    void setHistogram(std::string histogram);
    void calculateVariance();

};