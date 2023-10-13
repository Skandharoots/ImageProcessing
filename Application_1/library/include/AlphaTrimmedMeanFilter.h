
#include <string>
#include <exception>

class AlphaTrimmedMeanFilter {
    private:
        std::string inputPath;
        std::string outputPath;

    public:
        AlphaTrimmedMeanFilter(std::string inputPath, std::string outputPath);
        ~AlphaTrimmedMeanFilter();
        std::string getInputPath();
	    void setInputPath(std::string path);
	    std::string getOutputPath();
	    void setOutputPath(std::string path);
        float sort(float box[], int n, int d);
        void filter();
};