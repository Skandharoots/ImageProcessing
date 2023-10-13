
#include <string>
#include <exception>

class AlphaTrimmedMeanFilter {
    private:
        std::string inputPath;
        std::string outputPath;
    public:
        AlphaTrimmedMeanFilter();
        ~AlphaTrimmedMeanFilter();
        std::string getInputPath();
	    void setInputPath(std::string path);
	    std::string getOutputPath();
	    void setOutputPath(std::string path);
        void filter();
};