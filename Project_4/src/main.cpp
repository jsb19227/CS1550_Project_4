#include <iostream>
#include <string>
#include <unistd.h>

#include "common.h"
#include "fifoAlgorithm.h"

int main(int argc, char* argv[])
{
    uint8_t numFrames, inputArgs = 0x0F;
    uint16_t refresh;
    algo_t replacementAlgo;
    std::string filePath;
    
    int option = -1;
    while((option = getopt(argc, argv, "n:a:r:")) != -1)
    {
        switch(option)
        {
            case 'n':
                numFrames = static_cast<uint8_t>(std::stoi(optarg));
                inputArgs &= ~0x08;
                break;
            case 'a':
                if(static_cast<std::string>(optarg) == static_cast<std::string>("opt"))
                    replacementAlgo = opt;
                else if(static_cast<std::string>(optarg) == static_cast<std::string>("fifo"))
                    replacementAlgo = fifo;
                else if(static_cast<std::string>(optarg) == static_cast<std::string>("2nd"))
                    replacementAlgo = second;
                else if (static_cast<std::string>(optarg) == static_cast<std::string>("nru"))
                    replacementAlgo = nru;
                else
                {
                    std::cerr << "Usage -a <opt|fifo|2nd|nru>" << std::endl;
                    return 1;
                }
                inputArgs &= ~0x04;
                break;
            case 'r':
                refresh = static_cast<uint16_t>(std::stoi(optarg));
                inputArgs &= ~0x01;
                break;
            default:
                std::cerr << "Usage –n <numframes> -a <opt|fifo|2nd|nru> [-r <refresh>] <tracefile>" << std::endl;
                return 1;
        }
    }
    if(optind >= argc)
    {
        std::cerr << "Usage –n <numframes> -a <opt|fifo|2nd|nru> [-r <refresh>] <tracefile>" << std::endl;
        return 1;
    }
    filePath = argv[optind];
    inputArgs &= ~0x02;

    if(inputArgs >= 0x02)
    {
        std::cerr << "Usage –n <numframes> -a <opt|fifo|2nd|nru> [-r <refresh>] <tracefile>" << std::endl;
        return 1;
    }
    FIFOAlgorithm test(numFrames, filePath);
    test.runSimulation();
    
    return 0;
}