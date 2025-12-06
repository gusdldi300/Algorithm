
#include <iostream>
#include <climits>

#define STEPS_COUNT (2U)
#define SCORES_COUNT (3U)

static unsigned int sMaxScores[STEPS_COUNT][SCORES_COUNT] = { 0, };
static unsigned int sMinScores[STEPS_COUNT][SCORES_COUNT] = { 0, };

int main()
{
    unsigned int stepsCount = 0;
    std::cin >> stepsCount;
    std::cin >> sMaxScores[0][0] >> sMaxScores[0][1] >> sMaxScores[0][2];

    sMinScores[0][0] = sMaxScores[0][0];
    sMinScores[0][1] = sMaxScores[0][1];
    sMinScores[0][2] = sMaxScores[0][2];

    unsigned int stepScores[SCORES_COUNT] = { 0, };
    for (unsigned int step = 1; step < stepsCount; ++step)
    {
        std::cin >> stepScores[0] >> stepScores[1] >> stepScores[2];

        sMaxScores[1][0] = std::max(sMaxScores[0][0], sMaxScores[0][1]);
        sMaxScores[1][1] = std::max(sMaxScores[1][0], sMaxScores[0][2]);
        sMaxScores[1][2] = std::max(sMaxScores[0][1], sMaxScores[0][2]);

        sMinScores[1][0] = std::min(sMinScores[0][0], sMinScores[0][1]);
        sMinScores[1][1] = std::min(sMinScores[1][0], sMinScores[0][2]);
        sMinScores[1][2] = std::min(sMinScores[0][1], sMinScores[0][2]);

        for (unsigned int scoreIndex = 0; scoreIndex < SCORES_COUNT; ++scoreIndex)
        {
            sMaxScores[0][scoreIndex] = sMaxScores[1][scoreIndex] + stepScores[scoreIndex];
            sMinScores[0][scoreIndex] = sMinScores[1][scoreIndex] + stepScores[scoreIndex];
        }
    }

    unsigned int maxScore = 0;
    unsigned int minScore = UINT_MAX;
    for (unsigned int scoreIndex = 0; scoreIndex < SCORES_COUNT; ++scoreIndex)
    {
        maxScore = std::max(maxScore, sMaxScores[0][scoreIndex]);
        minScore = std::min(minScore, sMinScores[0][scoreIndex]);
    }

    std::cout << maxScore << " " << minScore;

    return 0;
}