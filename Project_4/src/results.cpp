#include "common.h"
#include "fifoAlgorithm.h"
#include "secondAlgorithm.h"
#include "nruAlgorithm.h"
#include "optAlgorithm.h"

void writeToFile(std::ofstream& file, VirtualMemorySimulation& sim);

int main()
{
    std::ofstream output("../extra/results.csv");

    uint32_t frameSizes[] = {8, 16, 32, 64};

    output << "opt algorithm on cc.trace" << std::endl;
    for(int i = 0; i < 4; i++)
    {
        OPTAlgorithm newSim(frameSizes[i], "../extra/cc.trace");
        newSim.runSimulation();
        std::cout << std::endl;
        writeToFile(output, newSim);
    }

    output << "opt algorithm on ls.trace" << std::endl;
    for(int i = 0; i < 4; i++)
    {
        OPTAlgorithm newSim(frameSizes[i], "../extra/ls.trace");
        newSim.runSimulation();
        std::cout << std::endl;
        writeToFile(output, newSim);
    }
    output << std::endl;
    output << "fifo algorithm on cc.trace" << std::endl;
    for(int i = 0; i < 4; i++)
    {
        FIFOAlgorithm newSim(frameSizes[i], "../extra/cc.trace");
        newSim.runSimulation();
        std::cout << std::endl;
        writeToFile(output, newSim);
    }

    output << "fifo algorithm on ls.trace" << std::endl;
    for(int i = 0; i < 4; i++)
    {
        FIFOAlgorithm newSim(frameSizes[i], "../extra/ls.trace");
        newSim.runSimulation();
        std::cout << std::endl;
        writeToFile(output, newSim);
    }
    output << std::endl;
    output << "2nd algorithm on cc.trace" << std::endl;
    for(int i = 0; i < 4; i++)
    {
        SecondAlgorithm newSim(frameSizes[i], "../extra/cc.trace");
        newSim.runSimulation();
        std::cout << std::endl;
        writeToFile(output, newSim);
    }

    output << "2nd algorithm on ls.trace" << std::endl;
    for(int i = 0; i < 4; i++)
    {
        SecondAlgorithm newSim(frameSizes[i], "../extra/ls.trace");
        newSim.runSimulation();
        std::cout << std::endl;
        writeToFile(output, newSim);
    }
    output << std::endl;
    output << "nru algorithm on cc.trace" << std::endl;
    for(int i = 0; i < 4; i++)
    {
        NRUAlgorithm newSim(frameSizes[i], "../extra/cc.trace", 6);
        newSim.runSimulation();
        std::cout << std::endl;
        writeToFile(output, newSim);
    }


    output << "nru algorithm on ls.trace" << std::endl;
    for(int i = 0; i < 4; i++)
    {
        NRUAlgorithm newSim(frameSizes[i], "../extra/ls.trace", frameSizes[i] / 2);
        newSim.runSimulation();
        std::cout << std::endl;
        writeToFile(output, newSim);
    }

    output.close();

    return 0;
}

void writeToFile(std::ofstream& file, VirtualMemorySimulation& sim)
{
    file << sim.getNumberOfFrames() << ", " << sim.getTotalMemoryAccess() << ", " << sim.getTotalPageFaults() << ", " << sim.getTotalWritesToDisk() << std::endl;
}