#pragma once

#include <vector>

#include "Person.h"

class BinarySearch
{
public:
    // Returns -1, if not found
    static int GetNumberFirstIndex(int searchNumber, const std::vector<int>& numbersAscend);
    static int GetNumberLastIndex(int searchNumber, const std::vector<int>& numbersAscend);
    
private:
    static void searchNumberFirstIndexRecursive(int* outIndex, int leftIndex, int rightIndex, int searchNumber, const std::vector<int>& numbersAscend);
    static void searchNumberLastIndexRecursive(int* outIndex, int leftIndex, int rightIndex, int searchNumber, const std::vector<int>& numbersAscend);
};

