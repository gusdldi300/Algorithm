#include <iostream>
#include <map>

int main()
{
    unsigned int testsCount;
    std::cin >> testsCount;

    for (unsigned int i = 0; i < testsCount; ++i)
    {
        unsigned int operationsCount;
        std::cin >> operationsCount;

        std::map<int, unsigned int> numberCountMapAscend;
        for (unsigned int j = 0; j < operationsCount; ++j)
        {
            char operation;
            int number;

            std::cin >> operation >> number;

            if (operation == 'I')
            {
                numberCountMapAscend[number]++;

                continue;
            }

            if (numberCountMapAscend.empty())
            {
                continue;
            }

            std::map<int, unsigned int>::iterator deleteIter;
            if (number == -1)
            {
                deleteIter = numberCountMapAscend.begin();
            }
            else
            {
                deleteIter = numberCountMapAscend.end();

                --deleteIter;
            }

            if (deleteIter->second <= 1)
            {
                numberCountMapAscend.erase(deleteIter);
            }
            else
            {
                --numberCountMapAscend[deleteIter->first];
            }
        }

        if (numberCountMapAscend.empty())
        {
            std::cout << "EMPTY" << '\n';
        }
        else
        {
            std::cout << numberCountMapAscend.rbegin()->first << ' ' << numberCountMapAscend.begin()->first << '\n';
        }
    }

    return 0;
}