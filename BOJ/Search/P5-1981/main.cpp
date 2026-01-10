
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>

#define MAX_ARRAY_SIZE (101U)
#define MAX_DIRECTIONS (4U)

struct Position
{
    int Row;
    int Col;
};

static const Position MOVE_DIRECTION_POSITIONS[MAX_DIRECTIONS] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
static unsigned int sArray[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
static int sArraySize;

static int GetNumberIndexFromRecursive(const std::vector<unsigned int>& numbersAscend, unsigned int number, int leftIndex, int rightIndex)
{
    if (leftIndex > rightIndex)
    {
        return -1;
    }

    int midIndex = (leftIndex + rightIndex) / 2;
    if (number == numbersAscend[midIndex])
    {
        return midIndex;
    }

    if (number < numbersAscend[midIndex])
    {
        return GetNumberIndexFromRecursive(numbersAscend, number, leftIndex, midIndex - 1);
    }

    return GetNumberIndexFromRecursive(numbersAscend, number, midIndex + 1, rightIndex);
}

static bool CanGoToExitInRangeOf(unsigned int minNumber, unsigned int maxNumber)
{
    bool bVisiteds[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = { false, };

    Position startPosition = { 0, 0 };

    std::queue<Position> positionQueue;
    positionQueue.push(startPosition);
    bVisiteds[0][0] = true;

    bool bArrived = false;
    while (positionQueue.empty() == false)
    {
        Position position = positionQueue.front();
        positionQueue.pop();

        if (position.Row == sArraySize - 1 && position.Col == sArraySize - 1)
        {
            bArrived = true;

            break;
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

            if (bVisiteds[nextRow][nextCol])
            {
                continue;
            }

            if (sArray[nextRow][nextCol] < minNumber || sArray[nextRow][nextCol] > maxNumber)
            {
                continue;
            }

            bVisiteds[nextRow][nextCol] = true;
            positionQueue.push({ nextRow ,nextCol });
        }
    }

    return bArrived;
}

int main()
{
    std::cin >> sArraySize;

    std::set<unsigned int> orderedNumberSet;
    std::vector<unsigned int> numbersAscend;
    numbersAscend.reserve(sArraySize * sArraySize + 1);

    for (int row = 0; row < sArraySize; ++row)
    {
        for (int col = 0; col < sArraySize; ++col)
        {
            std::cin >> sArray[row][col];
            orderedNumberSet.insert(sArray[row][col]);
        }
    }

    for (unsigned int number : orderedNumberSet)
    {
        numbersAscend.push_back(number);
    }

    unsigned int minNumber = sArray[0][0];
    unsigned int maxNumber = sArray[sArraySize - 1][sArraySize - 1];
    if (minNumber > maxNumber)
    {
        minNumber = sArray[sArraySize - 1][sArraySize - 1];
        maxNumber = sArray[0][0];
    }

    unsigned int minNumberIndex = GetNumberIndexFromRecursive(numbersAscend, minNumber, 0, numbersAscend.size() - 1);
    unsigned int maxNumberIndex = GetNumberIndexFromRecursive(numbersAscend, maxNumber, 0, numbersAscend.size() - 1);

    while (true)
    {
        if (CanGoToExitInRangeOf(numbersAscend[minNumberIndex], numbersAscend[maxNumberIndex]))
        {
            break;
        }
        
        if (minNumberIndex == 0)
        {
            maxNumberIndex++;
        }
        else if (maxNumberIndex == numbersAscend.size() - 1)
        {
            minNumberIndex--;
        }
        else
        {
            unsigned int minDifference = numbersAscend[minNumberIndex] - numbersAscend[minNumberIndex - 1];
            unsigned int maxDifference = numbersAscend[maxNumberIndex + 1] - numbersAscend[maxNumberIndex];
            if (minDifference <= maxDifference)
            {
                minNumberIndex--;
            }
            else
            {
                maxNumberIndex++;
            }
        }
    }
    
    std::cout << (numbersAscend[maxNumberIndex] - numbersAscend[minNumberIndex]);

    return 0;
}