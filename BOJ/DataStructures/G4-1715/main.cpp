
#include <iostream>
#include <queue>

int main()
{
    unsigned int cardBundlesCount;
    std::cin >> cardBundlesCount;

    std::priority_queue<unsigned int, std::vector<unsigned int>, std::greater<unsigned int>> cardBundleQueueAscend;
    for (unsigned int i = 0; i < cardBundlesCount; ++i)
    {
        unsigned int cardBundle;
        std::cin >> cardBundle;

        cardBundleQueueAscend.push(cardBundle);
    }

    unsigned int totalCompareCount = 0;
    while (cardBundleQueueAscend.size() > 1)
    {
        unsigned int minBundle = cardBundleQueueAscend.top();
        cardBundleQueueAscend.pop();

        minBundle += cardBundleQueueAscend.top();
        cardBundleQueueAscend.pop();

        totalCompareCount += minBundle;

        cardBundleQueueAscend.push(minBundle);
    }

    std::cout << totalCompareCount;

    return 0;
}