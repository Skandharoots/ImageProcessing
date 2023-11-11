#include <string>

class StandardDeviation {

private:
    std::string input;
    std::string output;
    std::string histogram;

public:
    StandardDeviation(std::string input, std::string histogram);
    ~StandardDeviation();
    std::string getInput();
    void setInput(std::string input);
    std::string getHistogram();
    void setHistogram(std::string histogram);
    void calculateStandardDeviation();

};