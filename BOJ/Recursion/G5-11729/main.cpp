
#include <cassert>
#include <iostream>
#include <cstdio>

#define ROD_SUM (6)

void PrintMovedDiskInOrderRecursive(unsigned int startRod, unsigned int endRod, const unsigned int moveDisks)
{
    if (moveDisks <= 0)    
    {
        return;
    }

    PrintMovedDiskInOrderRecursive(startRod, ROD_SUM - startRod - endRod, moveDisks - 1);
    //std::cout << startRod << ' ' << endRod << std::endl;
    printf("%d %d\n", startRod, endRod);
    PrintMovedDiskInOrderRecursive(ROD_SUM - startRod - endRod, endRod, moveDisks - 1);
}

int main()
{
    unsigned int disks = 0;
    std::cin >> disks;
    
    //assert(disks >= 1 && disks <= 20);
    //std::cout << (1 << disks) - 1 << std::endl;

    printf("%d\n", (1 << disks) - 1);
    PrintMovedDiskInOrderRecursive(1, 3, disks);

    return 0;
}