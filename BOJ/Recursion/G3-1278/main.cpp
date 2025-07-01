
#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>

static std::vector<unsigned int> sActorMoveOfScenes;
static std::vector<unsigned int> sMaxActorMoveOfScenes;
static std::unordered_set<unsigned int> sVisitedFlags;

static unsigned int sMaxActorCount = 0;

void GetMaxSceneRecursive(unsigned int actorBitFlagsOfScene)
{
    for (unsigned int actor = 0; actor < sMaxActorCount; ++actor)
    {
        // Actor on stage: Remove actor
        // Actor not on stage: Add actor
        unsigned int checkFlags = actorBitFlagsOfScene ^ (1 << actor);
        if (checkFlags == 0x00)
        {
            if (sActorMoveOfScenes.size() > sMaxActorMoveOfScenes.size())
            {
                sMaxActorMoveOfScenes = sActorMoveOfScenes;
                sMaxActorMoveOfScenes.push_back(actor + 1);
            }

            continue;
        }

        if (sVisitedFlags.find(checkFlags) != sVisitedFlags.end())
        {
            continue;
        }

        sActorMoveOfScenes.push_back(actor + 1);
        sVisitedFlags.insert(checkFlags);
        
        GetMaxSceneRecursive(checkFlags);
        
        //sVisitedFlags.erase(checkFlags);
        sActorMoveOfScenes.pop_back();
    }
}

int main()
{
    enum
    {
        MAX_SCENE_COUNT = (1 << 17) + 1
    };

    sActorMoveOfScenes.reserve(MAX_SCENE_COUNT);
    sMaxActorMoveOfScenes.reserve(MAX_SCENE_COUNT);
    sVisitedFlags.reserve(MAX_SCENE_COUNT);

    std::cin >> sMaxActorCount;

    std::cout << ((1 << sMaxActorCount) - 1) << std::endl;
    GetMaxSceneRecursive(0x00);

    for (unsigned int actor : sMaxActorMoveOfScenes)
    {
        //std::cout << actor << std::endl;
        printf("%d\n", actor);
    }
    
    return 0;
}

