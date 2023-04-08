#include "common.h"
#include "nruAlgorithm.h"

int main()
{
    std::ofstream output("../extra/refreshSize.csv");
    
    output << "refresh size, page faults 8, disk writes 8, page faults 16, disk writes 16,  page faults 32, disk writes 32,  page faults 64, disk writes 64" << std::endl;
    for(int i = 1; i <= 512; i = i << 1)
    {
        std::cout << i << ": " << std::endl;
        NRUAlgorithm size8(8, "cc.trace", i);
        NRUAlgorithm size16(16, "cc.trace", i);
        NRUAlgorithm size32(32, "cc.trace", i);
        NRUAlgorithm size64(64, "cc.trace", i);
        size8.runSimulation();
        size16.runSimulation();
        size32.runSimulation();
        size64.runSimulation();

        output << i << ", " << size8.getTotalPageFaults() << ", " << size8.getTotalWritesToDisk() << ", " << size16.getTotalPageFaults() << ", " << size16.getTotalWritesToDisk() << ", " << size32.getTotalPageFaults() << ", " << size32.getTotalWritesToDisk() << ", " << size64.getTotalPageFaults() << ", " << size64.getTotalWritesToDisk() << ", " << std::endl;
        std::cout << std::endl;
    }

    return 0;
}