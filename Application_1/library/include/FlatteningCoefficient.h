#include <string>

class FlatteningCoefficient {

private:
    std::string input;
    std::string output;
    std::string histogram;

public:
    FlatteningCoefficient(std::string input, std::string histogram);
    ~FlatteningCoefficient();
    std::string getInput();
    void setInput(std::string input);
    std::string getHistogram();
    void setHistogram(std::string histogram);
    void calculateFlatteningCoefficient();

};