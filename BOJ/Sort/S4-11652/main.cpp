
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<long long> cardsAscend;
    
    unsigned int cardsCount;
    std::cin >> cardsCount;

    for (unsigned int i = 0; i < cardsCount; ++i)
    {
        long long card;
        std::cin >> card;

        cardsAscend.push_back(card);
    }

    std::sort(cardsAscend.begin(), cardsAscend.end());

    long long mostCard = cardsAscend[0];
    unsigned int mostCardCount = 1;
     
    unsigned int equalCardCount = 1;
    for (unsigned int i = 1; i < cardsAscend.size(); ++i)
    {
        long long card = cardsAscend[i];
        
        if (card == cardsAscend[i - 1])
        {
            equalCardCount++;
            
            continue;
        }

        if (equalCardCount > mostCardCount)
        {
            mostCardCount = equalCardCount;
            mostCard = cardsAscend[i - 1];
        }
        
        equalCardCount = 1;
    }
    
    if (equalCardCount > mostCardCount)
    {
        mostCard = cardsAscend[cardsAscend.size() - 1];
    }

    std::cout << mostCard;

    return 0;
}