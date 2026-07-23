
#include <cassert>
#include <vector>

#include "MergeSort.h"

int main()
{
    std::vector<int> numbers = { -10 };
    MergeSort::SortAscend(&numbers);
    assert(numbers[0] == -10);

    numbers = { -10, -1 };
    MergeSort::SortAscend(&numbers);
    assert(numbers[0] == -10);
    assert(numbers[1] == -1);

    numbers = { -1, -10, 5, 2, 6, 5, 4 };
    MergeSort::SortAscend(&numbers);
    assert(numbers[0] == -10);
    assert(numbers[1] == -1);
    assert(numbers[2] == 2);
    assert(numbers[3] == 4);
    assert(numbers[4] == 5);
    assert(numbers[5] == 5);
    assert(numbers[6] == 6);

    numbers = { -1, -10, 5, 2, 6, 5, 4, -2 };
    MergeSort::SortAscend(&numbers);
    assert(numbers[0] == -10);
    assert(numbers[1] == -2);
    assert(numbers[2] == -1);
    assert(numbers[3] == 2);
    assert(numbers[4] == 4);
    assert(numbers[5] == 5);
    assert(numbers[6] == 5);
    assert(numbers[7] == 6);

    return 0;
}