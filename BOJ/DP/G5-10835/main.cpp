#include <iostream>

#define MAX_CARDS_COUNT (2001U)

static int sMaxPoints[MAX_CARDS_COUNT][MAX_CARDS_COUNT];

static unsigned int sLeftCards[MAX_CARDS_COUNT] = { 0, };
static unsigned int sRightCards[MAX_CARDS_COUNT] = { 0, };

static unsigned int GetMaxPointRecursive(unsigned int leftRemoveCount, unsigned int rightRemoveCount, const unsigned int cardsCount)
{
    if (leftRemoveCount == cardsCount || rightRemoveCount == cardsCount)
    {
        return 0;
    }
    
    if (sMaxPoints[leftRemoveCount][rightRemoveCount] > -1)
    {
        return sMaxPoints[leftRemoveCount][rightRemoveCount];
    }

    int removeRightPoint = 0;
    
    if (sRightCards[rightRemoveCount] < sLeftCards[leftRemoveCount])
    {
        removeRightPoint = sRightCards[rightRemoveCount];
        removeRightPoint += GetMaxPointRecursive(leftRemoveCount, rightRemoveCount + 1, cardsCount);
    }

    int maxPoint = std::max(GetMaxPointRecursive(leftRemoveCount + 1, rightRemoveCount + 1, cardsCount),
                                GetMaxPointRecursive(leftRemoveCount + 1, rightRemoveCount, cardsCount));

    maxPoint = std::max(maxPoint, removeRightPoint);
    sMaxPoints[leftRemoveCount][rightRemoveCount] = maxPoint;

    return maxPoint;
}

int main()
{
    unsigned int cardsCount;
    std::cin >> cardsCount;
    
    for (unsigned int leftIndex = 0; leftIndex < cardsCount; ++leftIndex)
    {
        std::cin >> sLeftCards[leftIndex];
    }

    for (unsigned int rightIndex = 0; rightIndex < cardsCount; ++rightIndex)
    {
        std::cin >> sRightCards[rightIndex];
    }

    for (unsigned int i = 0; i <= cardsCount; ++i)
    {
        for (unsigned int j = 0; j <= cardsCount; ++j)
        {
            sMaxPoints[i][j] = -1;
        }
    }

    std::cout << GetMaxPointRecursive(0, 0, cardsCount);

    return 0;
}