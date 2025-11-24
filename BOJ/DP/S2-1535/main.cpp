
#include <algorithm>
#include <iostream>
#include <vector>

#define MAX_HEALTH (100U)
#define MAX_COUNT (20U)

unsigned int sMaxScores[MAX_COUNT][MAX_HEALTH] = { 0, };

struct Greeting
{
    unsigned int TakeHealth;
    unsigned int Score;
};

int main()
{
    unsigned int targetCount = 0;
    std::cin >> targetCount;

    std::vector<Greeting> greetings;
    greetings.reserve(targetCount + 1);

    for (unsigned int count = 0; count < targetCount; ++count)
    {
        unsigned int takeHealth = 0;
        std::cin >> takeHealth;

        greetings.push_back({ takeHealth , 0 });
    }

    for (unsigned int count = 0; count < targetCount; ++count)
    {
        std::cin >> greetings[count].Score;
    }

    for (unsigned int health = greetings[0].TakeHealth; health < MAX_HEALTH; ++health)
    {
        sMaxScores[0][health] = greetings[0].Score;
    }

    for (unsigned int count = 1; count < targetCount; ++count)
    {
        for (unsigned int health = 0; health < MAX_HEALTH; ++health)
        {
            sMaxScores[count][health] = sMaxScores[count - 1][health];

            if (health >= greetings[count].TakeHealth)
            {
                sMaxScores[count][health] = std::max(sMaxScores[count][health],
                    greetings[count].Score + sMaxScores[count - 1][health - greetings[count].TakeHealth]);
            }
        }
    }
    
    std::cout << sMaxScores[targetCount - 1][MAX_HEALTH - 1];

    return 0;
}