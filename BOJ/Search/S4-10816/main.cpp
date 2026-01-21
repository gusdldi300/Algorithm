
#include <algorithm>
#include <iostream>
#include <vector>

#define MAX_CARDS_COUNT (500001U)

static unsigned int GetCardStartIndexFrom(const std::vector<int>& cardsAscend, int findCard)
{
    int startIndex = 0;
    int endIndex = static_cast<int>(cardsAscend.size()); 
    while (startIndex < endIndex)
    {
        int midIndex = (startIndex + endIndex) / 2;
        int midCard = cardsAscend[midIndex];
        
        if (findCard <= midCard)
        {
            endIndex = midIndex;
        }
        else
        {
            startIndex = midIndex + 1;
        }
    }

    return startIndex;
}

static unsigned int GetCardEndIndexFrom(const std::vector<int>& cardsAscend, int findCard)
{
    int startIndex = 0;
    int endIndex = static_cast<int>(cardsAscend.size());
    while (startIndex < endIndex)
    {
        int midIndex = (startIndex + endIndex) / 2;
        int midCard = cardsAscend[midIndex];

        if (findCard < midCard)
        {
            endIndex = midIndex;
        }
        else
        {
            startIndex = midIndex + 1;
        }
    }

    return endIndex;
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int cardsCount;
    std::cin >> cardsCount;

    std::vector<int> cardsAscend;
    for (unsigned int i = 0; i < cardsCount; ++i)
    {
        int card;
        std::cin >> card;

        cardsAscend.push_back(card);
    }

    std::sort(cardsAscend.begin(), cardsAscend.end());

    unsigned int findCardsCount;
    std::cin >> findCardsCount;
    
    for (unsigned int i = 0; i < findCardsCount; ++i)
    {
        int findCard;
        std::cin >> findCard;

        unsigned int startIndex = GetCardStartIndexFrom(cardsAscend, findCard);
        unsigned int endIndex = GetCardEndIndexFrom(cardsAscend, findCard);

        std::cout << (endIndex - startIndex) << ' ';
    }

    return 0;
}