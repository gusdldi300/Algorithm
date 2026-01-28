
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

int main()
{
    int solutionsCount;
    std::cin >> solutionsCount;

    std::vector<int> solutionsAscend;
    for (int i = 0; i < solutionsCount; ++i)
    {
        int solution;
        std::cin >> solution;

        solutionsAscend.push_back(solution);
    }

    int bestFirstSolution = 0;
    int bestSecondSolution = 0;
    int bestMixedDifference = INT_MAX;

    for (int i = 0; i < solutionsCount - 1; ++i)
    {
        int firstSolution = solutionsAscend[i];

        int startIndex = i + 1;
        int endIndex = solutionsCount - 1;

        while (startIndex <= endIndex)
        {
            int midIndex = (startIndex + endIndex) / 2;
            int secondSolution = solutionsAscend[midIndex];

            int mixedSolution = firstSolution + secondSolution;
            if (abs(mixedSolution) < bestMixedDifference)
            {
                bestFirstSolution = firstSolution;
                bestSecondSolution = secondSolution;

                bestMixedDifference = abs(mixedSolution);
            }

            if (mixedSolution == 0)
            {
                break;
            }
            else if (mixedSolution < 0)
            {
                startIndex = midIndex + 1;
            }
            else
            {
                endIndex = midIndex - 1;
            }
        }
    }

    std::cout << bestFirstSolution << " " << bestSecondSolution;

    return 0;
}