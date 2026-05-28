
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    int candidatesCount;
    std::cin >> candidatesCount;

    std::vector<int> skillsAscend;
    for (int i = 0; i < candidatesCount; ++i)
    {
        int skill;
        std::cin >> skill;

        skillsAscend.push_back(skill);
    }

    std::sort(skillsAscend.begin(), skillsAscend.end());

    unsigned long long teamsCount = 0;
    for (int firstIndex = 0; firstIndex < candidatesCount - 2; ++firstIndex)
    {
        for (int secondIndex = firstIndex + 1; secondIndex < candidatesCount - 1; ++secondIndex)
        {
            int targetSkill = -1 * (skillsAscend[firstIndex] + skillsAscend[secondIndex]);
            
            if (targetSkill < skillsAscend[secondIndex + 1])
            {
                break;       
            }
                
            if (targetSkill > skillsAscend[candidatesCount - 1])
            {
                continue;
            }

            std::vector<int>::iterator findIter = std::lower_bound(skillsAscend.begin() + secondIndex + 1, skillsAscend.end(), targetSkill);
            std::vector<int>::iterator findEndIter = std::upper_bound(skillsAscend.begin() + secondIndex + 1, skillsAscend.end(), targetSkill);

            teamsCount += static_cast<unsigned long long>(findEndIter - findIter);
        }
    }

    std::cout << teamsCount;

    return 0;
}