#include <string>

class VariationCoefficient {

private:
    std::string input;
    std::string output;
    std::string histogram;

public:
    VariationCoefficient(std::string input, std::string histogram);
    ~VariationCoefficient();
    std::string getInput();
    void setInput(std::string input);
    std::string getHistogram();
    void setHistogram(std::string histogram);
    void calculateVariationCoefficient();

};