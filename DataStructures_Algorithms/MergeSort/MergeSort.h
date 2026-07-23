#pragma once

#include <vector>

class MergeSort
{
public:
    static void SortAscend(std::vector<int>* outNumbers);

private:
    static void sortRecursive(std::vector<int>& outNumbers, std::vector<int>& tempNumbers, int beginIndex, int endIndex);

};

