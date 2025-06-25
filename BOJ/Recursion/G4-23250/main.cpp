
#include <iostream>
#include <cstdio>

#define ROD_SUM (6)

void PrintHanoiTurnBinarySearchedRecursive(unsigned int startRod, unsigned int endRod, const unsigned long long printTurn, const unsigned long long startTurn, const unsigned long long endTurn)
{
    unsigned long long checkTurn = (startTurn + endTurn) / 2;

    if (printTurn == checkTurn)
    {
        printf("%d %d", startRod, endRod);

        return;
    }

    if (printTurn < checkTurn)
    {
        PrintHanoiTurnBinarySearchedRecursive(startRod, ROD_SUM - startRod - endRod, printTurn, startTurn, checkTurn - 1);
    }
    else
    {
        PrintHanoiTurnBinarySearchedRecursive(ROD_SUM - startRod - endRod, endRod, printTurn, checkTurn + 1, endTurn);
    }
}

int main()
{
    unsigned int disks = 0;
    unsigned long long printTurn = 0;
    std::cin >> disks >> printTurn;

    unsigned long long totalTurn = (1LL << disks) - 1;
    PrintHanoiTurnBinarySearchedRecursive(1, 3, printTurn, 1, totalTurn);

    return 0;
}