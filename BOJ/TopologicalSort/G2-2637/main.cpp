
#include <iostream>
#include <map>
#include <queue>
#include <vector>

#define MAX_COMPONENTS_COUNT (101U)

struct RequiredComponent
{
    unsigned int Id;
    unsigned int Count;
};

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int componentsCount;
    std::cin >> componentsCount;
    
    unsigned int relationsCount;
    std::cin >> relationsCount;
    
    unsigned int nextComponentCounts[MAX_COMPONENTS_COUNT] = { 0, };

    std::vector<RequiredComponent> requiredComponents[MAX_COMPONENTS_COUNT];
    for (unsigned int i = 0; i < relationsCount; ++i)
    {
        unsigned int component;
        RequiredComponent requiredComponent;

        std::cin >> component >> requiredComponent.Id >> requiredComponent.Count;

        requiredComponents[component].push_back(requiredComponent);
        nextComponentCounts[requiredComponent.Id]++;
    }

    std::vector<unsigned int> endComponents;
    for (unsigned int component = 1; component <= componentsCount; ++component)
    {
        if (nextComponentCounts[component] == 0)
        {
            endComponents.push_back(component);
        }
    }

    std::map<unsigned int, unsigned int> basicComponentAndCountMapAscend;
    unsigned int componentCounts[MAX_COMPONENTS_COUNT] = { 0, };
    
    for (unsigned int i = 0; i < endComponents.size() - 1; ++i)
    {
        std::queue<unsigned int> componentQueue;
        componentQueue.push(endComponents[i]);

        while (componentQueue.empty() == false)
        {
            unsigned int component = componentQueue.front();
            componentQueue.pop();

            for (const RequiredComponent& requiredComponent : requiredComponents[component])
            {
                --nextComponentCounts[requiredComponent.Id];

                if (nextComponentCounts[requiredComponent.Id] == 0)
                {
                    componentQueue.push(requiredComponent.Id);
                }
            }
        }
    }

    componentCounts[componentsCount] = 1;

    std::queue<unsigned int> componentQueue;
    componentQueue.push(componentsCount);

    while (componentQueue.empty() == false)
    {
        unsigned int component = componentQueue.front();
        componentQueue.pop();

        if (requiredComponents[component].size() == 0)
        {
            basicComponentAndCountMapAscend[component] = componentCounts[component];
        }

        for (const RequiredComponent& requiredComponent : requiredComponents[component])
        {
            --nextComponentCounts[requiredComponent.Id];

            if (nextComponentCounts[requiredComponent.Id] == 0)
            {
                componentQueue.push(requiredComponent.Id);
            }

            componentCounts[requiredComponent.Id] += (requiredComponent.Count * componentCounts[component]);
        }
    }
    
    for (const std::pair<unsigned int, unsigned int>& basicComponentAndCountPair : basicComponentAndCountMapAscend)
    {
        std::cout << basicComponentAndCountPair.first << ' ' << basicComponentAndCountPair.second << '\n';
    }

    return 0;
}