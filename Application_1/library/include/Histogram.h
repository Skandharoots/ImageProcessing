#include <string>

class Histogram {

    private:
        std::string inputPath;
        std::string outputPath;
        std::string channelS;
        int channel;
    public:
        Histogram(std::string channelS, std::string input, std::string output);
        ~Histogram();
        std::string getInput();
        void setInput(std::string path);
        std::string getOutput();
        void setOutput(std::string path);
        std::string getChannel();
        void setChannel(std::string channel);
        void setChannelVal(int val);
        int getChannelVal();
        void parseChannel();
        void computeHistogram();
};