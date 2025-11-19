
#include <iostream>

#define MAX_SEQUENCE_SIZE (100000U)

int main()
{
    unsigned int sequence[MAX_SEQUENCE_SIZE];
    
    unsigned int sequence_size = 0;
    std::cin >> sequence_size;
        
    for (unsigned int i = 0; i < sequence_size; ++i)
    {
        std::cin >> sequence[i];
    }

    unsigned int biggerSmallerCount[2][MAX_SEQUENCE_SIZE] = { 0, };
    for (unsigned int i = 0; i < MAX_SEQUENCE_SIZE; ++i)
    {
        biggerSmallerCount[0][i] = 1;
        biggerSmallerCount[1][i] = 1;
    }

    for (unsigned int i = 1; i < sequence_size; ++i)
    {
        unsigned int lastIndex = i - 1;
        if (sequence[i] == sequence[lastIndex])
        {
            biggerSmallerCount[0][i] = biggerSmallerCount[0][lastIndex] + 1;
            biggerSmallerCount[1][i] = biggerSmallerCount[1][lastIndex] + 1;
        }
        else if (sequence[i] > sequence[lastIndex])
        {
            biggerSmallerCount[0][i] = biggerSmallerCount[0][lastIndex] + 1;
        }
        else
        {
            biggerSmallerCount[1][i] = biggerSmallerCount[1][lastIndex] + 1;
        }
    }

    unsigned int longestCount = 0;
    for (unsigned int i = 0; i < sequence_size; ++i)
    {
        longestCount = (biggerSmallerCount[0][i] > longestCount ? biggerSmallerCount[0][i] : longestCount);
        longestCount = (biggerSmallerCount[1][i] > longestCount ? biggerSmallerCount[1][i] : longestCount);
    }

    std::cout << longestCount;

    return 0;
}