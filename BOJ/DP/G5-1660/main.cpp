#include <vector>
#include <iostream>
#include <cassert>
#include <climits>

#define MAX_CANON_BALL_COUNT (300001U)

static std::vector<unsigned int> sTetrahedrons;

static unsigned int sUsedTetrahedrons[MAX_CANON_BALL_COUNT];

int main()
{
    unsigned int lastTriangle = 1;
    sTetrahedrons.push_back(lastTriangle);

    unsigned int edgeLength = 2;
    while (true)
    {
        lastTriangle += edgeLength;
        unsigned int tetrahedrons = sTetrahedrons[sTetrahedrons.size() - 1] + lastTriangle;

        if (tetrahedrons >= MAX_CANON_BALL_COUNT)
        {
            break;
        }

        sTetrahedrons.push_back(tetrahedrons);
        edgeLength++;
    }

    unsigned int cannonBallCount;
    std::cin >> cannonBallCount;
    
    for (unsigned int i = 1; i <= cannonBallCount; ++i)
    {
        sUsedTetrahedrons[i] = UINT_MAX;
    }
    

    for (unsigned int i = 1; i <= cannonBallCount; ++i)
    {
        for (unsigned int tetrahedrons : sTetrahedrons)
        {
            if (tetrahedrons > i)
            {
                break;
            }

            sUsedTetrahedrons[i] = std::min(sUsedTetrahedrons[i], sUsedTetrahedrons[i - tetrahedrons] + 1);
        }
    }

    std::cout << sUsedTetrahedrons[cannonBallCount];

    return 0;
}