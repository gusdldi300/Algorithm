
#include <iostream>

#define MAX_STUDENT_COUNT (1001U)

static unsigned int sScores[MAX_STUDENT_COUNT] = { 0, };
static unsigned int sMaxScores[MAX_STUDENT_COUNT] = { 0, };

int main()
{
    int studentCount;
    std::cin >> studentCount;

    for (int i = 0; i < studentCount; ++i)
    {
        std::cin >> sScores[i];
    }

    for (int i = 0; i < studentCount; ++i)
    {
        unsigned int minTeamScore = sScores[i];
        unsigned int maxTeamScore = sScores[i];

        for (int j = i; j >= 0; --j)
        {
            minTeamScore = std::min(minTeamScore, sScores[j]);
            maxTeamScore = std::max(maxTeamScore, sScores[j]);

            sMaxScores[i + 1] = std::max(sMaxScores[i + 1], sMaxScores[j] + maxTeamScore - minTeamScore);
        }
    }

    std::cout << sMaxScores[studentCount];

    return 0;
}