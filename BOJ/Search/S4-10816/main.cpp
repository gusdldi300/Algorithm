
#include <algorithm>
#include <iostream>
#include <vector>

static unsigned int GetCardsFoundCount(int findCard, const std::vector<int>& cardsAscend)
{
    unsigned int foundCount = 0;

    int startIndex = 0;
    int endIndex = cardsAscend.size() - 1;
    while (startIndex <= endIndex)
    {
        int midIndex = (startIndex + endIndex) / 2;
        int midCard = cardsAscend[midIndex];
        if (midCard == findCard)
        {
            // Count found cards
            for (int i = midIndex; i >= 0; --i)
            {
                if (cardsAscend[i] != findCard)
                {
                    break;
                }

                ++foundCount;
            }

            for (int i = midIndex + 1; i < cardsAscend.size(); ++i)
            {
                if (cardsAscend[i] != findCard)
                {
                    break;
                }

                ++foundCount;
            }

            break;
        }

        if (findCard < midCard)
        {
            endIndex = midIndex - 1;
        }
        else
        {
            startIndex = midIndex + 1;
        }
    }

    return foundCount;
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

        std::cout << GetCardsFoundCount(findCard, cardsAscend) << ' ';
    }

    return 0;
}