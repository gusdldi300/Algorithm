
#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>

#define MAX_MIXED_COUNT (3U)

struct MixedSolution
{
    long long Solutions[MAX_MIXED_COUNT];
    long long Sum;
};

int main()
{

    unsigned int solutionsCount;
    std::cin >> solutionsCount;

    std::vector<long long> solutionsAscend;
    for (unsigned int i = 0; i < solutionsCount; ++i)
    {
        long long solution;
        std::cin >> solution;

        solutionsAscend.push_back(solution);
    }
    
    std::sort(solutionsAscend.begin(), solutionsAscend.end());

    MixedSolution closestMixedSolution;
    closestMixedSolution.Sum = LLONG_MAX;

    for (unsigned int i = 0; i < solutionsCount - 2; ++i)
    {
        for (unsigned int j = i + 1; j < solutionsCount - 1; ++j)
        {
            long long tempSum = (solutionsAscend[i] + solutionsAscend[j]);

            auto searchBeginIter = solutionsAscend.begin() + j + 1;
            auto foundIter = std::lower_bound(searchBeginIter, solutionsAscend.end(), tempSum * -1LL);
            
            long long totalSum = 0;
            long long thirdSolution = 0;
            if (foundIter >= solutionsAscend.end())
            {
                thirdSolution = *(foundIter - 1);
                totalSum = thirdSolution + tempSum;
            }
            else
            {
                thirdSolution = *foundIter;
                totalSum = thirdSolution + tempSum;
                if (foundIter > searchBeginIter)
                {
                    long long mixedLower = (*(foundIter - 1)) + tempSum;

                    if (std::abs(mixedLower) < std::abs(totalSum))
                    {
                        totalSum = mixedLower;
                        thirdSolution = (*(foundIter - 1));
                    }
                }
            }

            if (std::abs(totalSum) < std::abs(closestMixedSolution.Sum))
            {
                closestMixedSolution.Solutions[0] = solutionsAscend[i];
                closestMixedSolution.Solutions[1] = solutionsAscend[j];
                closestMixedSolution.Solutions[2] = thirdSolution;

                closestMixedSolution.Sum = totalSum;
            }

            if (closestMixedSolution.Sum == 0)
            {
                goto FOUND_LABEL;
            }
        }
    }
    
FOUND_LABEL:

    for (unsigned int i = 0; i < MAX_MIXED_COUNT; ++i)
    {
        std::cout << closestMixedSolution.Solutions[i] << " ";
    }


    return 0;
}