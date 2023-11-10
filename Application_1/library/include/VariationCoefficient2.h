#include <string>

class VariationCoefficient2 {

private:
    std::string input;
    std::string histogram;

public:
    VariationCoefficient2(std::string input, std::string histogram);
    ~VariationCoefficient2();
    std::string getInput();
    void setInput(std::string input);
    std::string getHistogram();
    void setHistogram(std::string histogram);
    void calculateVariationCoefficient2();

};