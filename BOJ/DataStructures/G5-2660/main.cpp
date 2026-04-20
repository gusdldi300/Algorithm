
#include <climits>
#include <iostream>
#include <vector>
#include <queue>

#define MAX_CANDIDATES_COUNT (51U)

int main()
{
    unsigned int candidatesCount;
    std::cin >> candidatesCount;

    std::vector<unsigned int> candidatesConnections[MAX_CANDIDATES_COUNT];

    while (true)
    {
        int firstCandidate;
        int secondCandidate;
        std::cin >> firstCandidate >> secondCandidate;

        if (firstCandidate == -1)
        {
            break;
        }

        candidatesConnections[firstCandidate].push_back(secondCandidate);
        candidatesConnections[secondCandidate].push_back(firstCandidate);
    }

    unsigned int candidatesScore[MAX_CANDIDATES_COUNT] = { 0, };
    unsigned int minScore = UINT_MAX;

    for (unsigned int candidate = 1; candidate <= candidatesCount; ++candidate)
    {
        unsigned int candidateScore = 0;

        bool bVisited[MAX_CANDIDATES_COUNT] = { false, };

        std::queue<unsigned int> candidateQueue;
        candidateQueue.push(candidate);
        bVisited[candidate] = true; 

        while (true)
        {
            unsigned int queueSize = candidateQueue.size();
            for (unsigned int i = 0; i < queueSize; ++i)
            {
                unsigned int curCandidate = candidateQueue.front();
                candidateQueue.pop();

                for (unsigned int nextCandidate : candidatesConnections[curCandidate])
                {
                    if (bVisited[nextCandidate])
                    {
                        continue;
                    }

                    candidateQueue.push(nextCandidate);
                    bVisited[nextCandidate] = true;
                }
            }

            if (candidateQueue.empty())
            {
                break;
            }

            ++candidateScore;
        }

        candidatesScore[candidate] = candidateScore;
        minScore = std::min(minScore, candidateScore);
    }

    std::vector<unsigned int> presidentsAscend;
    for (unsigned int candidate = 1; candidate <= candidatesCount; ++candidate)
    {
        if (candidatesScore[candidate] == minScore)
        {
            presidentsAscend.push_back(candidate);
        }
    }

    std::cout << minScore << ' ' << presidentsAscend.size() << '\n';

    for (unsigned int president : presidentsAscend)
    {
        std::cout << president << ' ';
    }

    return 0;
}