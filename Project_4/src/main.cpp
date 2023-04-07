#include <iostream>
#include <string>
#include <unistd.h>

#include "common.h"

uint8_t getNumberOfFrames(int argc, char* argv[]);
algo_t getAlgorithmChoice(int argc, char* argv[]);
uint8_t getRefresh(int argc, char* argv[]);
std::string getFilePath(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    uint8_t numFrames, refresh;
    algo_t replacementAlgo;
    std::string filePath;
    
    int operator = -1;
    while((operator = getopt(argc, argv, "n:")) != -1)
    {
        switch(operator)
        {
            case 'n':
                numFrames = static_cast<uint8_t>(std::stoi(optarg));
                break;
            case 'a':
                switch(optarg)
                {
                    case "opt":
                        replacementAlgo = opt;
                        break;
                }
            default:
                std::cerr << "Usage -n is –n <numframes>" << std::endl;
        }
    }

    return 0;
}

uint8_t getNumberOfFrames(int argc, char* argv[])
{
    int opt, n = -1;
    while((opt = getopt(argc, argv, "n:")) != -1)
    {
        switch(opt)
        {
            case 'n':
                n = std::stoi(optarg);
                break;
            default:
                std::cerr << "Usage -n is –n <numframes>" << std::endl;
        }
    }
    if(n == -1)
        std::cerr << "Number of frames required..." << std::endl;
    return n;
}