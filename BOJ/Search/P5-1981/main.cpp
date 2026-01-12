
#include <algorithm>
#include <iostream>
#include <queue>
#include <climits>

#define MAX_ARRAY_SIZE (101U)
#define MAX_DIRECTIONS (4U)

struct Position
{
    int Row;
    int Col;
};

static const Position MOVE_DIRECTION_POSITIONS[MAX_DIRECTIONS] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
static int sArray[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
static int sArraySize;

static bool HasReachedExit(int minNumber, int maxNumber)
{
    if (sArray[0][0] < minNumber || sArray[0][0] > maxNumber)
    {
        return false;
    }

    bool visiteds[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = { false, };

    Position startPosition = { 0 , 0 };
    std::queue<Position> positionQueue;
    positionQueue.push(startPosition);
    visiteds[0][0] = true;

    while (positionQueue.empty() == false)
    {
        Position position = positionQueue.front();
        positionQueue.pop();

        if (position.Row == sArraySize - 1 && position.Col == sArraySize - 1)
        {
            return true;
        }

        for (unsigned int dirIndex = 0; dirIndex < MAX_DIRECTIONS; ++dirIndex)
        {
            int nextRow = position.Row + MOVE_DIRECTION_POSITIONS[dirIndex].Row;
            int nextCol = position.Col + MOVE_DIRECTION_POSITIONS[dirIndex].Col;

            if (nextRow < 0 || nextRow >= sArraySize ||
                nextCol < 0 || nextCol >= sArraySize)
            {
                continue;
            }

            if (visiteds[nextRow][nextCol])
            {
                continue;
            }

            if (sArray[nextRow][nextCol] < minNumber || sArray[nextRow][nextCol] > maxNumber)
            {
                continue;
            }

            visiteds[nextRow][nextCol] = true;
            positionQueue.push({ nextRow ,nextCol });
        }
    }

    return false;
}

static void GetMinDifferenceMoveRecursive(int left, int right, int maxDifference, int* outMinDifference)
{
    if (left > right)
    {
        return;
    }

    int midDifference = (left + right) / 2;
    int maxNumber = midDifference;

    bool bArrived = false;
    for (int minNumber = 0; minNumber <= (maxDifference - midDifference); ++minNumber)
    {
        bArrived = HasReachedExit(minNumber, maxNumber);
        if (bArrived)
        {
            *outMinDifference = midDifference;

            break;
        }
        
        maxNumber++;
    }

    if (bArrived)
    {
        GetMinDifferenceMoveRecursive(left, midDifference - 1, maxDifference, outMinDifference);
    }
    else
    {
        GetMinDifferenceMoveRecursive(midDifference + 1, right, maxDifference, outMinDifference);
    }
}

int main()
{
    std::cin >> sArraySize;
    
    int minNumber = UINT_MAX;
    int maxNumber = 0;

    for (int row = 0; row < sArraySize; ++row)
    {
        for (int col = 0; col < sArraySize; ++col)
        {
            int number;

            std::cin >> number;

            sArray[row][col] = number;
            minNumber = std::min(minNumber, number);
            maxNumber = std::max(maxNumber, number);
        }
    }

    int minDifference = 0;
    GetMinDifferenceMoveRecursive(0, (maxNumber - minNumber), (maxNumber - minNumber), &minDifference);
    
    std::cout << minDifference;

    return 0;
}