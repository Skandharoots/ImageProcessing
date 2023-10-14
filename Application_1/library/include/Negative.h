#include <string>

class Negative {
private:
	std::string input;
	std::string output;

public:
	Negative(std::string input, std::string output);
	~Negative();
	std::string getInputPath();
	void setInputPath(std::string path);
	std::string getOutputPath();
	void setOutputPath(std::string path);
	void negate();
};