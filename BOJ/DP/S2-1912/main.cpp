
#include <algorithm>
#include <iostream>
#include <climits>

#define MAX_SEQUENCE_SIZE (100000U)

static int sSeqeunce[MAX_SEQUENCE_SIZE] = { 0, };
static int sMaxSums[MAX_SEQUENCE_SIZE] = { 0, };

int main()
{
    unsigned int sequence_size = 0;
    std::cin >> sequence_size;

    std::cin >> sSeqeunce[0];
    sMaxSums[0] = sSeqeunce[0];

    for (unsigned int i = 1; i < sequence_size; ++i)
    {
        std::cin >> sSeqeunce[i];

        sMaxSums[i] = sSeqeunce[i];
        
        if (sMaxSums[i - 1] > 0)
        {
            sMaxSums[i] += sMaxSums[i - 1];
        }
    }

    int maxSum = INT_MIN;
    for (unsigned int i = 0; i < sequence_size; ++i)
    {
        if (sMaxSums[i] > maxSum)
        {
            maxSum = sMaxSums[i];
        }
    }

    std::cout << maxSum;

    return 0;
}