#pragma once

#include <vector>

class QuickSort
{
public:
    static void SortAscend(std::vector<int>* outNumbers);

private:
    static void sortRecursive(std::vector<int>& outNumbers, int leftIndex, int rightIndex);
    static void swapNumber(int* pFirstNumber, int* pSecondNumber);
};

