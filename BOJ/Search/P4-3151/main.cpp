
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    unsigned int scoresCount;
    std::cin >> scoresCount;

    std::vector<int> scores;
    for (unsigned int i = 0; i < scoresCount; ++i)
    {
        int score;
        std::cin >> score;

        scores.push_back(score);
    }

    std::sort(scores.begin(), scores.end());

    long long foundCount = 0;
    for (std::vector<int>::iterator iter = scores.begin(); iter != scores.end(); ++iter)
    {
        int firstScore = *iter;
        for (std::vector<int>::iterator searchStartIter = iter + 1; searchStartIter != scores.end(); ++searchStartIter)
        {
            int scoreSum = firstScore + (*searchStartIter);
            
            int searchScore = scoreSum * -1;
            auto foundStartIter = std::lower_bound(searchStartIter + 1, scores.end(), searchScore);
            if (foundStartIter != scores.end() && (*foundStartIter) == searchScore)
            {
                auto foundEndIter = std::upper_bound(searchStartIter + 1, scores.end(), searchScore);
                foundCount += static_cast<long long>(foundEndIter - foundStartIter);
            }
        }
    }

    std::cout << foundCount;

    return 0;
}