
#include <iostream>

#define MAX_TIME (10001U)
#define MAX_CHAPTER (101U)

static unsigned int sMaxScores[MAX_CHAPTER][MAX_TIME] = { 0, };

int main()
{
    unsigned int targetChapter = 0;
    unsigned int targetTime = 0;

    std::cin >> targetChapter >> targetTime;

    unsigned int usedTime;
    unsigned int score;
    std::cin >> usedTime >> score;

    for (unsigned int time = usedTime; time <= targetTime; ++time)
    {
        sMaxScores[1][time] = score;
    }

    for (unsigned int chapter = 2; chapter <= targetChapter; ++chapter)
    {
        std::cin >> usedTime >> score;

        for (unsigned int time = 1; time < usedTime; ++time)
        {
            sMaxScores[chapter][time] = sMaxScores[chapter - 1][time];
        }

        for (unsigned int time = usedTime; time <= targetTime; ++time)
        {
            sMaxScores[chapter][time] = std::max(sMaxScores[chapter - 1][time], sMaxScores[chapter - 1][time - usedTime] + score);
        }
    }

    std::cout << sMaxScores[targetChapter][targetTime];

    return 0;
}