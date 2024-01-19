#include <string>
#include <complex>
#include <vector>
#include "CImg.h"

using namespace cimg_library;

class FastFourierTransform {

private:
    std::string inputPath;
    std::string outputPath;
    std::string outputPath2;
public:
    FastFourierTransform(std::string inputPath, std::string outputPath);
    ~FastFourierTransform();
    std::string getInputPath();
    void setInputPath(std::string path);
    std::string getOutputPath();
    void setOutputPath(std::string path);
    std::vector<std::complex<double>> forward();
    std::vector<std::complex<double>> fft(std::vector<std::complex<double>> a);
    std::vector<std::complex<double>> center(std::vector<std::complex<double>> a);
    std::vector<std::complex<double>> ifft(std::vector<std::complex<double>> a);
    void transform();
};