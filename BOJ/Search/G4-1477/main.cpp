
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    unsigned int existSheltersCount;
    unsigned int buildSheltersCount;

    unsigned int roadLength;

    std::cin >> existSheltersCount >> buildSheltersCount >> roadLength;

    std::vector<unsigned int> sheltersAscend;
    for (unsigned int i = 0; i < existSheltersCount; ++i)
    {
        unsigned int shelter;
        std::cin >> shelter;

        sheltersAscend.push_back(shelter);
    }

    std::sort(sheltersAscend.begin(), sheltersAscend.end());
    sheltersAscend.push_back(roadLength);

    unsigned int endLength = 0;
    unsigned int lastShelter = 0;

    for (unsigned int i = 0; i < sheltersAscend.size(); ++i)
    {
        unsigned int shelter = sheltersAscend[i];
        unsigned int length = shelter - lastShelter;

        endLength = std::max(endLength, length);

        lastShelter = shelter;
    }

    // 82 201 411 555 622 755

    // 70, 271, 341, 481, 551, 622, 692
    // 70, 82, 152, 201, 271, 341, 411, 481, 551, 555, 622, 692, 755

    unsigned int minDiffLength = endLength;
    unsigned int startLength = 0;

    while (startLength <= endLength)
    {
        unsigned int checkLength = (startLength + endLength) / 2;

        unsigned int buildCount = buildSheltersCount;
        unsigned int sheltersIndex = 0;
        unsigned int shelter = 0;

        bool bAvailable = true;
        while (shelter < roadLength)
        {
            unsigned int nextShelter = sheltersAscend[sheltersIndex];

            while ((shelter + checkLength) < nextShelter)
            {
                if (buildCount <= 0)
                {
                    bAvailable = false;

                    goto JUMP_LABEL;
                }

                shelter += checkLength;

                --buildCount;
            }

            sheltersIndex++;

            shelter = nextShelter;
        }

    JUMP_LABEL:
        if (bAvailable)
        {
            minDiffLength = std::min(minDiffLength, checkLength);

            endLength = checkLength - 1;
        }
        else
        {
            startLength = checkLength + 1;
        }
    }

    std::cout << minDiffLength;

    return 0;
}

