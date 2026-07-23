
#include <cassert>
#include <iostream>

#include "QuickSort.h"

int main()
{
    std::vector<int> numbers;
    QuickSort::SortAscend(&numbers);

    numbers = { 1 };
    QuickSort::SortAscend(&numbers);
    assert(numbers[0] = 1);

    numbers = { 3, 1, 7, 10, 8, -1 };
    QuickSort::SortAscend(&numbers);
    assert(numbers[0] = -1);
    assert(numbers[1] = 1);
    assert(numbers[2] = 3);
    assert(numbers[3] = 7);
    assert(numbers[4] = 8);
    assert(numbers[5] = 10);

    numbers = { -1, -2, -3, -4, -5, 10 };
    assert(numbers[0] = -5);
    assert(numbers[1] = -4);
    assert(numbers[2] = -3);
    assert(numbers[3] = -2);
    assert(numbers[4] = -1);
    assert(numbers[5] = 10);

    numbers = { 9, 1, 8, 2, 7, 3 };
    assert(numbers[0] = 1);
    assert(numbers[1] = 2);
    assert(numbers[2] = 3);
    assert(numbers[3] = 7);
    assert(numbers[4] = 8);
    assert(numbers[5] = 9);

    std::cout << "Test complete" << std::endl;

    return 0;
}