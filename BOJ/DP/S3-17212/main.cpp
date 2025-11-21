
#include <iostream>

#define MAX_PAY_AMOUNT (100001U)

unsigned int sMinCoinCounts[MAX_PAY_AMOUNT] = { 0, };

int main()
{
    unsigned int targetPayAmount = 0;
    std::cin >> targetPayAmount;

    sMinCoinCounts[1] = 1;
    sMinCoinCounts[2] = 1;
    sMinCoinCounts[3] = 2;
    sMinCoinCounts[4] = 2;
    sMinCoinCounts[5] = 1;
    sMinCoinCounts[6] = 2;
    sMinCoinCounts[7] = 1;

    for (unsigned int payAmount = 8; payAmount <= targetPayAmount; ++payAmount)
    {
        sMinCoinCounts[payAmount] = sMinCoinCounts[payAmount - 1];
        
        if (sMinCoinCounts[payAmount - 2] < sMinCoinCounts[payAmount])
        {
            sMinCoinCounts[payAmount] = sMinCoinCounts[payAmount - 2];
        }

        if (sMinCoinCounts[payAmount - 5] < sMinCoinCounts[payAmount])
        {
            sMinCoinCounts[payAmount] = sMinCoinCounts[payAmount - 5];
        }

        if (sMinCoinCounts[payAmount - 7] < sMinCoinCounts[payAmount])
        {
            sMinCoinCounts[payAmount] = sMinCoinCounts[payAmount - 7];
        }

        sMinCoinCounts[payAmount]++;
    }

    std::cout << sMinCoinCounts[targetPayAmount];

    return 0;
}