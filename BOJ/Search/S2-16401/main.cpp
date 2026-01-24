#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int main()
{
    unsigned int nephewsCount;
    unsigned int snacksCount;

    std::cin >> nephewsCount >> snacksCount;

    unsigned int endLength = 0;

    std::vector<unsigned int> snacks;
    for (unsigned int i = 0; i < snacksCount; ++i)
    {
        unsigned int snack;
        std::cin >> snack;

        snacks.push_back(snack);

        if (snack > endLength)
        {
            endLength = snack;
        }
    }

    assert(endLength != 0);
    unsigned int startLength = 1;

    unsigned int longestLength = 0;

    while (startLength <= endLength)
    {
        int midLength = (endLength + startLength) / 2;
        
        unsigned int eatableSnack = 0;
        for (unsigned int snackLength : snacks)
        {
            eatableSnack += (snackLength / midLength);
        }

        if (eatableSnack >= nephewsCount)
        {
            longestLength = midLength;

            startLength = midLength + 1;
        }
        else
        {
            endLength = midLength - 1;
        }
    }

    std::cout << longestLength;

    return 0;
}