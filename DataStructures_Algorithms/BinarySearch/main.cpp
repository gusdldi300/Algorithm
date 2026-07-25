
#include <cassert>
#include <vector>

#include "BinarySearch.h"

int main()
{
    // Test GetNumberFirstIndex() even numbers size 
    {
        std::vector<int> numbersAscend = { -1, 2, 3, 4, 5, 5, 5, 5, 8, 20 };
        for (int i = 0; i < numbersAscend.size(); ++i)
        {
            if (i == 4 || i == 5 || i == 6 || i == 7)
            {
                continue;
            }

            assert(BinarySearch::GetNumberFirstIndex(numbersAscend[i], numbersAscend) == i);
        }

        assert(BinarySearch::GetNumberFirstIndex(-5, numbersAscend) == -1);
        assert(BinarySearch::GetNumberFirstIndex(50, numbersAscend) == -1);
        assert(BinarySearch::GetNumberFirstIndex(5, numbersAscend) == 4);
    }

    // Test GetNumberFirstIndex() odd numbers size 
    {
        std::vector<int> numbersAscend = { -1, 2, 3, 4, 5, 5, 5, 8, 20 };
        for (int i = 0; i < numbersAscend.size(); ++i)
        {
            if (i == 4 || i == 5 || i == 6)
            {
                continue;
            }

            assert(BinarySearch::GetNumberFirstIndex(numbersAscend[i], numbersAscend) == i);
        }

        assert(BinarySearch::GetNumberFirstIndex(-5, numbersAscend) == -1);
        assert(BinarySearch::GetNumberFirstIndex(50, numbersAscend) == -1);
        assert(BinarySearch::GetNumberFirstIndex(5, numbersAscend) == 4);
    }


    // Test GetNumberLastIndex() even numbers size 
    {
        std::vector<int> numbersAscend = { -1, 2, 3, 4, 5, 5, 5, 5, 8, 20 };
        for (int i = 0; i < numbersAscend.size(); ++i)
        {
            if (i == 4 || i == 5 || i == 6 || i == 7)
            {
                continue;
            }

            assert(BinarySearch::GetNumberFirstIndex(numbersAscend[i], numbersAscend) == i);
        }

        assert(BinarySearch::GetNumberLastIndex(-5, numbersAscend) == -1);
        assert(BinarySearch::GetNumberLastIndex(50, numbersAscend) == -1);
        assert(BinarySearch::GetNumberLastIndex(5, numbersAscend) == 7);
    }


    // Test GetNumberLastIndex() odd numbers size 
    {
        std::vector<int> numbersAscend = { -1, 2, 3, 4, 5, 5, 5, 8, 20 };
        for (int i = 0; i < numbersAscend.size(); ++i)
        {
            if (i == 4 || i == 5 || i == 6)
            {
                continue;
            }

            assert(BinarySearch::GetNumberLastIndex(numbersAscend[i], numbersAscend) == i);
        }

        assert(BinarySearch::GetNumberLastIndex(-5, numbersAscend) == -1);
        assert(BinarySearch::GetNumberLastIndex(50, numbersAscend) == -1);
        assert(BinarySearch::GetNumberLastIndex(5, numbersAscend) == 6);
    }

    // Test 
    {
        std::vector<int> numbersAscend = { -1, -1, -1, 3, 3, 5, 5, 5, 8, 8, 20, 20 };

        assert(BinarySearch::GetNumberFirstIndex(-1, numbersAscend) == 0);
        assert(BinarySearch::GetNumberLastIndex(-1, numbersAscend) == 2);

        assert(BinarySearch::GetNumberFirstIndex(3, numbersAscend) == 3);
        assert(BinarySearch::GetNumberLastIndex(3, numbersAscend) == 4);

        assert(BinarySearch::GetNumberFirstIndex(5, numbersAscend) == 5);
        assert(BinarySearch::GetNumberLastIndex(5, numbersAscend) == 7);

        assert(BinarySearch::GetNumberFirstIndex(8, numbersAscend) == 8);
        assert(BinarySearch::GetNumberLastIndex(8, numbersAscend) == 9);

        assert(BinarySearch::GetNumberFirstIndex(20, numbersAscend) == 10);
        assert(BinarySearch::GetNumberLastIndex(20, numbersAscend) == 11);
    }

    return 0;
}