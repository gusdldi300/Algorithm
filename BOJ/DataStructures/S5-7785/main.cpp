
#include <iostream>
#include <set>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int workersCount;
    std::cin >> workersCount;

    std::set<std::string> workersInCompanyAscend;
    for (unsigned int i = 0; i < workersCount; ++i)
    {
        std::string worker;
        std::string state;

        std::cin >> worker >> state;

        if (state == "enter")
        {
            workersInCompanyAscend.insert(worker);
        }
        else
        {
            workersInCompanyAscend.erase(worker);
        }
    }

    for (auto rIter = workersInCompanyAscend.rbegin(); rIter != workersInCompanyAscend.rend(); ++rIter)
    {
        std::cout << *rIter << '\n';
    }

    return 0;
}