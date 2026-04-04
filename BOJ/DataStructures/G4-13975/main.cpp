
#include <iostream>
#include <queue>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int testsCount;
    std::cin >> testsCount;

    for (unsigned int test = 0; test < testsCount; ++test)
    {
        unsigned int chaptersCount;
        std::cin >> chaptersCount;

        std::priority_queue<unsigned long long, std::vector<unsigned long long>, std::greater<unsigned long long>> chapterPricesAscend;
        for (unsigned int chapter = 0; chapter < chaptersCount; ++chapter)
        {
            unsigned long long price;
            std::cin >> price;

            chapterPricesAscend.push(price);
        }

        unsigned long long totalPrice = 0;
        while (chapterPricesAscend.size() > 1)
        {
            unsigned long long addedPrice = chapterPricesAscend.top();
            chapterPricesAscend.pop();

            addedPrice += chapterPricesAscend.top();
            chapterPricesAscend.pop();

            totalPrice += addedPrice;
            chapterPricesAscend.push(addedPrice);
        }

        std::cout << totalPrice << '\n';
    }

    return 0;
}