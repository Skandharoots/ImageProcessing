#include <string>

class AssymetryCoefficient {

private:
    std::string input;
    std::string output;
    std::string histogram;

public:
    AssymetryCoefficient(std::string input, std::string histogram);
    ~AssymetryCoefficient();
    std::string getInput();
    void setInput(std::string input);
    std::string getHistogram();
    void setHistogram(std::string histogram);
    void calculateAssymetryCoefficient();

};