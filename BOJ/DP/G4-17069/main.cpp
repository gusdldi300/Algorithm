
#include <iostream>
#include <queue>

#define MAX_HOUSE_SIZE (33U)
#define MAX_PIPES_COUNT (3U)

enum class PipeDirection : unsigned int 
{
    Horizontal = 0,
    Vertical,
    Diagonal
};

struct Position
{
    int Row;
    int Col;
};

struct SpaceInfo
{
    Position Pos;
    PipeDirection PipeState;
};

// H, V, D
static const std::vector<PipeDirection> NEXT_PIPE_DIRECTIONS[MAX_PIPES_COUNT] = 
{
    { PipeDirection::Horizontal, PipeDirection::Diagonal },
    { PipeDirection::Vertical, PipeDirection::Diagonal },
    { PipeDirection::Horizontal, PipeDirection::Vertical, PipeDirection::Diagonal }
};

static const std::vector<Position> PIPE_CHECK_POSITIONS[MAX_PIPES_COUNT] =
{
    { { 0, 1 } },
    { { 1, 0 } },
    { { 0, 1 }, { 1, 0 }, { 1, 1 } }
};

static const Position PIPE_SET_POSITIONS[MAX_PIPES_COUNT] =
{
    { 0, 1 },
    { 1, 0 },
    { 1, 1 }
};

static bool sbWall[MAX_HOUSE_SIZE][MAX_HOUSE_SIZE] = { false, };
static unsigned long long sPipeCases[MAX_PIPES_COUNT][MAX_HOUSE_SIZE][MAX_HOUSE_SIZE] = { 0, };

static unsigned int sHouseSize;

static unsigned long long GetHousePipeCaseRecursive(const SpaceInfo& spaceInfo)
{
    if (spaceInfo.Pos.Row == sHouseSize - 1 && spaceInfo.Pos.Col == sHouseSize - 1)
    {
        return 1;
    }

    unsigned long long pipeCase = 0;
    unsigned int pipeIndex = static_cast<unsigned int>(spaceInfo.PipeState);

    if (sPipeCases[pipeIndex][spaceInfo.Pos.Row][spaceInfo.Pos.Col] > 0)
    {
        return sPipeCases[pipeIndex][spaceInfo.Pos.Row][spaceInfo.Pos.Col];
    }

    for (PipeDirection nextPipe : NEXT_PIPE_DIRECTIONS[pipeIndex])
    {
        unsigned int nextPipeIndex = static_cast<unsigned int>(nextPipe);

        bool bPlaceable = true;
        for (const Position& checkPosition : PIPE_CHECK_POSITIONS[nextPipeIndex])
        {
            int nextRow = spaceInfo.Pos.Row + checkPosition.Row;
            int nextCol = spaceInfo.Pos.Col + checkPosition.Col;

            if ((nextRow < 0 || nextRow >= sHouseSize || nextCol < 0 || nextCol >= sHouseSize) ||
                sbWall[nextRow][nextCol])
            {
                bPlaceable = false;

                break;
            }
        }

        if (bPlaceable)
        {
            Position nextPosition = PIPE_SET_POSITIONS[nextPipeIndex];
            nextPosition.Row += spaceInfo.Pos.Row;
            nextPosition.Col += spaceInfo.Pos.Col;

            pipeCase += GetHousePipeCaseRecursive({ nextPosition, nextPipe });
        }
    }

    sPipeCases[pipeIndex][spaceInfo.Pos.Row][spaceInfo.Pos.Col] = pipeCase;
    
    return pipeCase;
}

int main()
{
    std::cin >> sHouseSize;

    for (unsigned int row = 0; row < sHouseSize; ++row)
    {
        for (unsigned int col = 0; col < sHouseSize; ++col)
        {
            unsigned int state;
            std::cin >> state;
            
            sbWall[row][col] = ((state == 1) ? true : false);
        }
    }

    SpaceInfo startInfo = { { 0, 1 }, PipeDirection::Horizontal };
    
    unsigned long long pipeCase = GetHousePipeCaseRecursive(startInfo);
    
    std::cout << pipeCase;

    return 0;
}