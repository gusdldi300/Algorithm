
#include <iostream>
#include <queue>

#define MAX_ROOM_SIZE (301)
#define MAX_PROLIFERATE_POSITIONS_SIZE (8U)
struct Position
{
    int Row;
    int Col;
};

static const Position PROLIFERATE_POSITIONS[MAX_PROLIFERATE_POSITIONS_SIZE] =
{
    { -1, -2 },
    { -2, -1 },

    { -2, 1 },
    { -1, 2 },

    { 1, 2 },
    { 2, 1 },

    { 2, -1 },
    { 1, -2 },
};

static bool sbVisited[2][MAX_ROOM_SIZE][MAX_ROOM_SIZE] = {false,};

int main()
{
    unsigned int roomSize;
    unsigned int moldsCount;
    unsigned int cleanCheckCount;
    unsigned int daysLeft;

    std::cin >> roomSize >> moldsCount >> cleanCheckCount >> daysLeft;

    std::queue<Position> moldPositions;

    for (unsigned int i = 0; i < moldsCount; ++i)
    {
        Position moldPosition;
        std::cin >> moldPosition.Col >> moldPosition.Row;
        --moldPosition.Col;
        --moldPosition.Row;

        moldPositions.push(moldPosition);
    }

    std::queue<Position> cleanCheckPositions;
    for (unsigned int i = 0; i < cleanCheckCount; ++i)
    {
        Position checkPosition;
        std::cin >> checkPosition.Col >> checkPosition.Row;
        --checkPosition.Col;
        --checkPosition.Row;

        cleanCheckPositions.push(checkPosition);
    }

    unsigned int daysPassed = 1;
    while ((moldPositions.empty() == false) && (daysPassed <= daysLeft))
    {
        unsigned int moldsSize = moldPositions.size();
        for (unsigned int mold = 0; mold < moldsSize; ++mold)
        {
            Position position = moldPositions.front();
            moldPositions.pop();

            unsigned int checkTime = daysPassed % 2;
            for (unsigned int i = 0; i < MAX_PROLIFERATE_POSITIONS_SIZE; ++i)
            {
                int nextRow = position.Row + PROLIFERATE_POSITIONS[i].Row;
                int nextCol = position.Col + PROLIFERATE_POSITIONS[i].Col;

                if (nextRow < 0 || nextRow >= roomSize ||
                    nextCol < 0 || nextCol >= roomSize)
                {
                    continue;
                }

                if (sbVisited[checkTime][nextRow][nextCol])
                {
                    continue;
                }

                sbVisited[checkTime][nextRow][nextCol] = true;
                moldPositions.push({ nextRow, nextCol });
            }
        }
        
        ++daysPassed;
    }

    unsigned int checkTime = daysLeft % 2;
    while (cleanCheckPositions.empty() == false)
    {
        Position checkPosition = cleanCheckPositions.front();
        cleanCheckPositions.pop();

        if (sbVisited[checkTime][checkPosition.Row][checkPosition.Col])
        {
            std::cout << "YES";

            return 0;
        }
    }

    std::cout << "NO";

    return 0;
}