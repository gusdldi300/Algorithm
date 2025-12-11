
#include <iostream>
#include <queue>
#include <unordered_set>

#define MAX_MAZE_SIZE (50)
#define MAX_CHECK_DIRECTIONS_SIZE (4U)

#define MAX_KEYS_COUNT (6U)
#define ALL_KEYS_MASK (64U)

#define SHIFT_BIT_LEFT(count)   \
            (1 << (count))        \

#define ADD_KEY(keyIndex, containedKeys)                    \
            (containedKeys |= SHIFT_BIT_LEFT(keyIndex))     \

#define HAS_KEY(keyIndex, containedKeys)                                          \
            (((containedKeys & SHIFT_BIT_LEFT(keyIndex)) > 0) ? true : false)       \

struct Position
{
    int Row;
    int Col;
};

struct State
{
    Position Pos;
    unsigned int Keys;
    unsigned int MoveCount;
};

const static Position CHECK_DIRECTIONS[MAX_CHECK_DIRECTIONS_SIZE] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

static int sMazeSizeRow;
static int sMazeSizeCol;

static char sMaze[MAX_MAZE_SIZE][MAX_MAZE_SIZE] = { 0, };
static bool sVisited[ALL_KEYS_MASK][MAX_MAZE_SIZE][MAX_MAZE_SIZE] = { false, };

static std::unordered_set<char> sTotalKeys;
static std::unordered_set<char> sTotalDoors;

int main()
{
    std::cin >> sMazeSizeRow >> sMazeSizeCol;
    
    State startState = { 0, };
    for (int row = 0; row < sMazeSizeRow; ++row)
    {
        std::string rowMazeString;
        std::cin >> rowMazeString;

        for (int col = 0; col < sMazeSizeCol; ++col)
        {
            sMaze[row][col] = rowMazeString[col];

            if (sMaze[row][col] == '0')
            {
                startState.Pos.Row = row;
                startState.Pos.Col = col;
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

    State exitState = { 0, };

    std::queue<State> stateQueue;
    stateQueue.push(startState);
    sVisited[startState.Keys][startState.Pos.Row][startState.Pos.Col] = true;

    while (stateQueue.empty() == false)
    {
        State state = stateQueue.front();
        stateQueue.pop();

        if (sMaze[state.Pos.Row][state.Pos.Col] == '1')
        {
            exitState = state;

            break;
        }

        for (unsigned int dirIndex = 0; dirIndex < MAX_CHECK_DIRECTIONS_SIZE; ++dirIndex)
        {
            int nextRow = state.Pos.Row + CHECK_DIRECTIONS[dirIndex].Row;
            int nextCol = state.Pos.Col + CHECK_DIRECTIONS[dirIndex].Col;

            if (nextRow < 0 || nextRow >= sMazeSizeRow || nextCol < 0 || nextCol >= sMazeSizeCol)
            {
                continue;
            }

            char mazeState = sMaze[nextRow][nextCol];
            if (mazeState == '#' || sVisited[state.Keys][nextRow][nextCol])
            {
                continue;
            }

            if (sTotalDoors.find(mazeState) != sTotalDoors.end() && HAS_KEY(mazeState - 'A', state.Keys) == false)
            {
                continue;
            }

            sVisited[state.Keys][nextRow][nextCol] = true;

            unsigned int nextKeys = state.Keys;
            if (sTotalKeys.find(mazeState) != sTotalKeys.end())
            {
                ADD_KEY(mazeState - 'a', nextKeys);
                sVisited[nextKeys][nextRow][nextCol] = true;
            }

            stateQueue.push({ { nextRow, nextCol }, nextKeys, state.MoveCount + 1 });
        }
    }

    if (exitState.MoveCount == 0)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << exitState.MoveCount;
    }

    return 0;
}
