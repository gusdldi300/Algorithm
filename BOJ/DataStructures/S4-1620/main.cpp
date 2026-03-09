
#include <iostream>
#include <unordered_map>
#include <string>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int monstersCount;
    unsigned int problemsCount;
    std::cin >> monstersCount >> problemsCount;

    std::unordered_map<std::string, unsigned int> monsterIndexMap;
    std::unordered_map<unsigned int, std::string> indexMonsterMap;
    for (unsigned int index = 1; index <= monstersCount; ++index)
    {
        std::string monster;
        std::cin >> monster;

        monsterIndexMap.insert(std::pair<std::string, unsigned int>(monster, index));
        indexMonsterMap.insert(std::pair<unsigned int, std::string>(index, monster));
    }

    for (unsigned int i = 0; i < problemsCount; ++i)
    {
        std::string problem;
        std::cin >> problem;

        if (monsterIndexMap.find(problem) == monsterIndexMap.end())
        {
            unsigned int monsterIndex = std::stoi(problem);

            std::cout << indexMonsterMap[monsterIndex] << '\n';
        }
        else
        {
            std::cout << monsterIndexMap[problem] << '\n';
        }
    }

    return 0;
}