
#include <iostream>
#include <queue>
#include <unordered_set>

#define MAX_MAZE_SIZE (50)
#define MAX_CHECK_DIRECTIONS_SIZE (4U)

#define MAX_KEYS_COUNT (6U)

#define SHIFT_BIT_LEFT(count)   \
            (1 << count)        \

#define SET_VISITED_MASK(row, col, visitedMasks)        \
            (visitedMasks[row] |= SHIFT_BIT_LEFT(col))  \

#define ADD_KEY(keyIndex, containedKeys)                     \
            (containedKeys |= SHIFT_BIT_LEFT(key))      \

#define HAS_VISITED(row, col, visitedMasks)                                  \
            ((visitedMasks[row] & SHIFT_BIT_LEFT(col)) > 0 ? true : false)   \

#define HAS_KEY(keyIndex, containedKeys)                                          \
            ((containedKeys & SHIFT_BIT_LEFT(keyIndex)) > 0 ? true : false)       \

struct Position
{
    int Row;
    int Col;
};

const static Position CHECK_DIRECTIONS[MAX_CHECK_DIRECTIONS_SIZE] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

static int sMazeSizeRow;
static int sMazeSizeCol;

static std::unordered_set<char> sTotalKeys;
static std::unordered_set<char> sTotalDoors;

static char sMaze[MAX_MAZE_SIZE][MAX_MAZE_SIZE] = { 0, };

static int GetExitMazeMinMoveRecursive(const Position& startPosition, unsigned int lastKeys, int lastMoveCount)
{
    unsigned long long visitedMasks[MAX_MAZE_SIZE] = { 0, };

    std::queue<Position> positionQueue;
    positionQueue.push(startPosition);
    
    SET_VISITED_MASK(startPosition.Row, startPosition.Col, visitedMasks);

    int totalMoveCount = INT_MAX;
    int moveCount = lastMoveCount;

    while (positionQueue.empty() == false)
    {
        Position position = positionQueue.front();
        positionQueue.pop();

        ++moveCount;
        
        if (sMaze[position.Row][position.Col] == '1')
        {
            return moveCount;
        }

        for (unsigned int dirIndex = 0; dirIndex < MAX_CHECK_DIRECTIONS_SIZE; ++dirIndex)
        {
            int nextRow = position.Row + CHECK_DIRECTIONS[dirIndex].Row;
            int nextCol = position.Col + CHECK_DIRECTIONS[dirIndex].Col;

            if (nextRow < 0 || nextRow >= sMazeSizeRow || nextCol < 0 || nextCol >= sMazeSizeCol)
            {
                continue;
            }

            char state = sMaze[nextRow][nextCol];

            if (state == '#' || HAS_VISITED(nextRow, nextCol, visitedMasks))
            {
                continue;
            }

            if (sTotalDoors.find(state) != sTotalDoors.end() && HAS_KEY(state - 'A', lastKeys) == false)
            {
                continue;
            }

            SET_VISITED_MASK(nextRow, nextCol, visitedMasks);

            if (sTotalKeys.find(state) != sTotalKeys.end() && HAS_KEY(state - 'a', lastKeys) == false)
            {
                unsigned int keys = lastKeys;
                ADD_KEY(state - 'a', keys);

                totalMoveCount = std::min(totalMoveCount, GetExitMazeMinMoveRecursive({ nextRow, nextCol }, keys, moveCount - 1));

                continue;
            }
            
            positionQueue.push({ nextRow, nextCol });
        }
    }

    return totalMoveCount;
}

int main()
{
    std::cin >> sMazeSizeRow >> sMazeSizeCol;
    
    Position startPosition = { 0, };
    for (int row = 0; row < sMazeSizeRow; ++row)
    {
        std::string rowMazeString;
        std::cin >> rowMazeString;

        for (int col = 0; col < sMazeSizeCol; ++col)
        {
            sMaze[row][col] = rowMazeString[col];

            if (sMaze[row][col] == '0')
            {
                startPosition = { row, col };
            }
        }
    }

    sTotalKeys.insert('a');
    sTotalKeys.insert('b');
    sTotalKeys.insert('c');
    sTotalKeys.insert('d');
    sTotalKeys.insert('e');
    sTotalKeys.insert('f');

    sTotalDoors.insert('A');
    sTotalDoors.insert('B');
    sTotalDoors.insert('C');
    sTotalDoors.insert('D');
    sTotalDoors.insert('E');
    sTotalDoors.insert('F');

    std::cout << GetExitMazeMinMoveRecursive(startPosition, 0, 0);

    return 0;
}