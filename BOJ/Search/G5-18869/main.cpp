
#include <iostream>
#include <set>
#include <vector>

#define MAX_SPACES_COUNT (101U)

int main()
{
    unsigned int spacesCount;
    unsigned int planetsCount;
    std::cin >> spacesCount >> planetsCount;

    std::vector<unsigned int> spaces[MAX_SPACES_COUNT];
    std::vector<unsigned int> spacesUniqueAscend[MAX_SPACES_COUNT];

    for (unsigned int i = 0; i < spacesCount; ++i)
    {
        std::set<unsigned int> planetsSetAscend;

        for (unsigned int j = 0; j < planetsCount; ++j)
        {
            unsigned int planet;
            std::cin >> planet;

            spaces[i].push_back(planet);
            planetsSetAscend.insert(planet);
        }

        for (unsigned int planet : planetsSetAscend)
        {
            spacesUniqueAscend[i].push_back(planet);
        }
    }

    // Compress coordinates
    std::vector<unsigned int> spacesIndexes[MAX_SPACES_COUNT];
    for (unsigned int i = 0; i < spacesCount; ++i)
    {
        for (unsigned int searchPlanet : spaces[i])
        {
            auto foundIter = std::lower_bound(spacesUniqueAscend[i].begin(), spacesUniqueAscend[i].end(), searchPlanet);
            
            unsigned int foundIndex = static_cast<unsigned int>(foundIter - spacesUniqueAscend[i].begin());
            spacesIndexes[i].push_back(foundIndex);
        }
    }

    unsigned int equalSpacesCount = 0;
    for (unsigned int i = 0; i < spacesCount; ++i)
    {
        for (unsigned int j = i + 1; j < spacesCount; ++j)
        {
            bool bEqual = true;

            if (spacesIndexes[i] == spacesIndexes[j])
            {
                equalSpacesCount++;
            }
        }
    }
    
    std::cout << equalSpacesCount;

    return 0;
}