
#include <iostream>
#include <cassert>
#include <queue>

#define MAX_MAP_SIZE (50U)
#define MAX_KEY_COUNT (251U)

#define MAX_CHECK_DIRECTIONS_SIZE (4U)

struct Position
{
    int Row;
    int Col;
};

struct State
{
    Position Pos;
    unsigned int MoveCount;
};

static const Position CHECK_DIRECTIONS[MAX_CHECK_DIRECTIONS_SIZE] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

static int sMapSize;
static unsigned int sMaxKeyCount;

static int sMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
static bool sbVisited[MAX_KEY_COUNT][MAX_MAP_SIZE][MAX_MAP_SIZE] = { false, };

static unsigned int sKeyAquiredMoveCounts[MAX_KEY_COUNT] = { 0, };

static bool HasAllKeys()
{
    for (unsigned int key = 1; key <= sMaxKeyCount; ++key)
    {
        if (sKeyAquiredMoveCounts[key] == 0)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    std::cin >> sMapSize >> sMaxKeyCount;

    std::queue<State> startStates;
    unsigned int keyCount = 0;
    for (int row = 0; row < sMapSize; ++row)
    {
        std::string mapRowString;
        std::cin >> mapRowString;

        for (int col = 0; col < sMapSize; ++col)
        {
            switch (mapRowString[col])
            {
            case '0':
                sMap[row][col] = 0;

                break;
            case '1':
                sMap[row][col] = -1;

                break;
            case 'S':
                // Intentional fallthrough
            case 'K':
                startStates.push({ { row, col }, 0 });
                
                sMap[row][col] = keyCount;
                ++keyCount;

                break;
            default:
                assert(false);
            }
        }
    }

    for (unsigned int startKey = 0; startKey < sMaxKeyCount; ++startKey)
    {
        State startState = startStates.front();
        startStates.pop();

        std::queue<State> stateQueue;
        stateQueue.push(startState);
        sbVisited[startKey][startState.Pos.Row][startState.Pos.Col] = true;

        while (stateQueue.empty() == false)
        {
            State state = stateQueue.front();
            stateQueue.pop();

            for (unsigned int dirIndex = 0; dirIndex < MAX_CHECK_DIRECTIONS_SIZE; ++dirIndex)
            {
                int nextRow = state.Pos.Row + CHECK_DIRECTIONS[dirIndex].Row;
                int nextCol = state.Pos.Col + CHECK_DIRECTIONS[dirIndex].Col;

                if (nextRow < 0 || nextRow >= sMapSize ||
                    nextCol < 0 || nextCol >= sMapSize)
                {
                    continue;
                }

                if (sMap[nextRow][nextCol] == -1 || sbVisited[startKey][nextRow][nextCol])
                {
                    continue;
                }

                unsigned int nextMove = state.MoveCount + 1;
                unsigned int keyNumber = static_cast<unsigned int>(sMap[nextRow][nextCol]);

                if (keyNumber > startKey)
                {
                    if (sKeyAquiredMoveCounts[keyNumber] == 0)
                    {
                        sKeyAquiredMoveCounts[keyNumber] = nextMove;
                    }
                    else
                    {
                        sKeyAquiredMoveCounts[keyNumber] = std::min(sKeyAquiredMoveCounts[keyNumber], nextMove);
                    }
                }

                sbVisited[startKey][nextRow][nextCol] = true;
                stateQueue.push({ { nextRow, nextCol }, nextMove });
            }
        }
    }

    

    unsigned int totalMoveCount = 0;
    for (unsigned int i = 1; i <= sMaxKeyCount; ++i)
    {
        totalMoveCount += sKeyAquiredMoveCounts[i];
    }

    if (HasAllKeys() == false)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << totalMoveCount;
    }
    
    return 0;
}