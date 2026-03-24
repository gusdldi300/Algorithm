
#include <iostream>
#include <vector>
#include <set>
#include <cassert>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int placesCount;
    unsigned int queriesCount;
    
    std::cin >> placesCount >> queriesCount;

    std::set<unsigned int> sights;
    for (unsigned int place = 0; place < placesCount; ++place)
    {
        unsigned int isSight;
        std::cin >> isSight;
        
        if (isSight == 1)
        {
            sights.insert(place);
        }
    }

    unsigned int currentPlace = 0;
    
    for (unsigned int i = 0; i < queriesCount; ++i)
    {
        unsigned int query;
        std::cin >> query;

        switch (query)
        {
        case 1:
        {
            unsigned int newSight;
            std::cin >> newSight;
            --newSight;

            if (sights.find(newSight) != sights.end())
            {
                sights.erase(newSight);
            }
            else
            {
                sights.insert(newSight);
            }

            break;
        }
        case 2:
        {
            unsigned int moveCount;
            std::cin >> moveCount;

            currentPlace = (currentPlace + moveCount) % placesCount;

            break;
        }
        case 3:
        {
            if (sights.empty())
            {
                std::cout << -1 << '\n';

                break;
            }

            unsigned int moveCount = 0;
            auto equalHigherIter = sights.lower_bound(currentPlace);

            if (equalHigherIter == sights.end())
            {
                moveCount = placesCount - currentPlace + (*sights.begin());
            }
            else
            {
                moveCount = (*equalHigherIter) - currentPlace;
            }

            std::cout << moveCount << '\n';

            break;
        }
        default:
            assert(false);
        }
    }

    return 0;
}