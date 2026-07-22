
#include <cassert>
#include <iostream>
#include <vector>

#include "BubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"

int main()
{
    // Test BubbleSort
    {
        std::vector<int> bubbleSortedNumbers({ 10, 7, 4, 5, -1 });

        BubbleSort::SortAscend(&bubbleSortedNumbers);
        assert(bubbleSortedNumbers[0] == -1);
        assert(bubbleSortedNumbers[1] == 4);
        assert(bubbleSortedNumbers[2] == 5);
        assert(bubbleSortedNumbers[3] == 7);
        assert(bubbleSortedNumbers[4] == 10);
    }

    // Test SelectionSort
    {
        std::vector<int> selectionSortedNumbers({ 10, 7, 4, 5, -1 });
        SelectionSort::SortAscend(&selectionSortedNumbers);
        assert(selectionSortedNumbers[0] == -1);
        assert(selectionSortedNumbers[1] == 4);
        assert(selectionSortedNumbers[2] == 5);
        assert(selectionSortedNumbers[3] == 7);
        assert(selectionSortedNumbers[4] == 10);
    }

    // Test InsertionSort
    {
        std::vector<int> selectionSortedNumbers({ -1, 5, 10, 7, 4 });
        InsertionSort::SortDescend(&selectionSortedNumbers);
        assert(selectionSortedNumbers[0] == 10);
        assert(selectionSortedNumbers[1] == 7);
        assert(selectionSortedNumbers[2] == 5);
        assert(selectionSortedNumbers[3] == 4);
        assert(selectionSortedNumbers[4] == -1);
    }

    std::cout << "Test complete\n";

    return 0;
}