
#include <iostream>
#include <queue>

#define MAX_ARRAY_SIZE (101U)
#define MAX_DIRECTIONS (4U)

struct Position
{
    int Row;
    int Col;
};

struct ArrayInfo
{
    Position Pos;
    unsigned int MaxNumber;
    unsigned int MinNumber;
};

static const Position MOVE_DIRECTION_POSITIONS[MAX_DIRECTIONS] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

static unsigned int sArray[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
static ArrayInfo sMinInfos[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = { 0, };

int main()
{
    int arraySize;
    std::cin >> arraySize;

    for (int row = 0; row < arraySize; ++row)
    {
        for (int col = 0; col < arraySize; ++col)
        {
            std::cin >> sArray[row][col];

            sMinInfos[row][col].Pos.Row = -1;
            sMinInfos[row][col].Pos.Col = -1;
        }
    }

    ArrayInfo startInfo;
    startInfo.Pos.Row = 0;
    startInfo.Pos.Col = 0;
    startInfo.MaxNumber = sArray[0][0];
    startInfo.MinNumber = startInfo.MaxNumber;
    
    sMinInfos[0][0] = startInfo;
    std::queue<ArrayInfo*> pArrayInfoQueue;
    pArrayInfoQueue.push(&sMinInfos[0][0]);

    while (pArrayInfoQueue.empty() == false)
    {
        const ArrayInfo* pArrayInfo = pArrayInfoQueue.front();
        pArrayInfoQueue.pop();

        if (pArrayInfo->Pos.Row == arraySize - 1 && pArrayInfo->Pos.Col == arraySize - 1)
        {
            break;
        }

        for (unsigned int dirIndex = 0; dirIndex < MAX_DIRECTIONS; ++dirIndex)
        {
            int nextRow = pArrayInfo->Pos.Row + MOVE_DIRECTION_POSITIONS[dirIndex].Row;
            int nextCol = pArrayInfo->Pos.Col + MOVE_DIRECTION_POSITIONS[dirIndex].Col;

            if (nextRow < 0 || nextRow >= arraySize ||
                nextCol < 0 || nextCol >= arraySize)
            {
                continue;
            }

            unsigned int nextNumber = sArray[nextRow][nextCol];
            unsigned int nextMaxNumber = std::max(pArrayInfo->MaxNumber, nextNumber);
            unsigned int nextMinNumber = std::min(pArrayInfo->MinNumber, nextNumber);

            if (sMinInfos[nextRow][nextCol].Pos.Row > -1)
            {
                if ((nextMaxNumber - nextMinNumber) < (sMinInfos[nextRow][nextCol].MaxNumber - sMinInfos[nextRow][nextCol].MinNumber))
                {
                    sMinInfos[nextRow][nextCol].MaxNumber = nextMaxNumber;
                    sMinInfos[nextRow][nextCol].MinNumber = nextMinNumber;
                }

                continue;
            }

            sMinInfos[nextRow][nextCol].Pos = { nextRow, nextCol };
            sMinInfos[nextRow][nextCol].MaxNumber = nextMaxNumber;
            sMinInfos[nextRow][nextCol].MinNumber = nextMinNumber;

            pArrayInfoQueue.push(&sMinInfos[nextRow][nextCol]);
        }
    }
    
    std::cout << (sMinInfos[arraySize - 1][arraySize - 1].MaxNumber - sMinInfos[arraySize - 1][arraySize - 1].MinNumber);

    return 0;
}