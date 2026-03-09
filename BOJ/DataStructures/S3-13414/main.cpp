
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int maxAcceptCount;
    unsigned int inputCount;

    std::cin >> maxAcceptCount >> inputCount;

    std::vector<std::string> clickedIds;
    std::unordered_map<std::string, unsigned int> studentIdPriorityMap;
    for (unsigned int priority = 0; priority < inputCount; ++priority)
    {
        std::string studentId;
        std::cin >> studentId;
    
        clickedIds.push_back(studentId);
        studentIdPriorityMap[studentId] = priority;
    }
    
    unsigned int acceptCount = 0;
    for (unsigned int priority = 0; priority < inputCount; ++priority)
    {
        if (acceptCount >= maxAcceptCount)
        {
            break;
        }

        const std::string& studentId = clickedIds[priority];

        if (studentIdPriorityMap[studentId] != priority)
        {
            continue;
        }

        ++acceptCount;
        std::cout << studentId << '\n';
    }

    return 0;
}