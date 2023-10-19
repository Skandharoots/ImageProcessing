
#include <string>
#include <exception>

class AlphaTrimmedMeanFilter {
    private:
        std::string inputPath;
        std::string outputPath;
        std::string values;
        int d;

    public:
        AlphaTrimmedMeanFilter(std::string values, std::string inputPath, std::string outputPath);
        ~AlphaTrimmedMeanFilter();
        std::string getInputPath();
	    void setInputPath(std::string path);
	    std::string getOutputPath();
	    void setOutputPath(std::string path);
        std::string getValues();
	    void setValues(std::string value);
        int getD();
        void setD(int d);
        void parseValues();
        float sort(float box[], int n, int d);
        void filter();
};