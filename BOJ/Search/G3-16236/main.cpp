#include <iostream>
#include <queue>

#define MAX_MAP_SIZE (20U)
#define MAX_MOVE_DIRECTIONS (4U)
#define INIT_SHARK_SIZE (2U)

struct Position
{
    int Row;
    int Col;
};

struct BabyShark
{
    unsigned int Size;
    unsigned int FishAteCount;
    Position Pos;
};

// N, E, S, W
static const Position MOVE_DIRECTIONS[] =
{
    { -1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, -1 }
};

static int sMapSize;
static unsigned int sMap[MAX_MAP_SIZE][MAX_MAP_SIZE];

static unsigned int GetShortestDistanceFish(const BabyShark& babyShark, Position* outFish)
{
    std::vector<Position> eatableFishes;

    std::queue<Position> queuePosition;
    queuePosition.push(babyShark.Pos);

    bool bVisited[MAX_MAP_SIZE][MAX_MAP_SIZE] = { false, };
    bVisited[babyShark.Pos.Row][babyShark.Pos.Col] = true;

    unsigned int moveCount = 0;
    while (queuePosition.empty() == false)
    {
        unsigned int queueSize = queuePosition.size();
        for (unsigned int i = 0; i < queueSize; ++i)
        {
            Position position = queuePosition.front();
            queuePosition.pop();

            for (unsigned int moveIndex = 0; moveIndex < MAX_MOVE_DIRECTIONS; ++moveIndex)
            {
                int nextRow = position.Row + MOVE_DIRECTIONS[moveIndex].Row;
                int nextCol = position.Col + MOVE_DIRECTIONS[moveIndex].Col;

                if (nextRow < 0 || nextRow >= sMapSize || nextCol < 0 || nextCol >= sMapSize)
                {
                    continue;
                }

                if (bVisited[nextRow][nextCol])
                {
                    continue;
                }

                if (babyShark.Size < sMap[nextRow][nextCol])
                {
                    continue;
                }

                if (babyShark.Size == sMap[nextRow][nextCol] || sMap[nextRow][nextCol] == 0)
                {
                    bVisited[nextRow][nextCol] = true;
                    queuePosition.push({ nextRow, nextCol });

                    continue;
                }

                eatableFishes.push_back({ nextRow, nextCol });
            }
        }

        ++moveCount;

        if (eatableFishes.size() > 0)
        {
            break;
        }
    }

    if (eatableFishes.size() <= 0)
    {
        return 0;
    }

    Position candidateFish = { MAX_MAP_SIZE, MAX_MAP_SIZE };
    for (const Position& fish : eatableFishes)
    {
        if (candidateFish.Row < fish.Row)
        {
            continue;
        }
        else if (candidateFish.Row == fish.Row)
        {
            if (candidateFish.Col < fish.Col)
            {
                continue;
            }
        }
        
        candidateFish = fish;
    }

    *outFish = candidateFish;

    return moveCount;
}

int main()
{
    std::cin >> sMapSize;

    BabyShark babyShark;
    babyShark.Size = INIT_SHARK_SIZE;
    babyShark.FishAteCount = 0;

    for (int row = 0; row < sMapSize; ++row)
    {
        for (int col = 0; col < sMapSize; ++col)
        {
            std::cin >> sMap[row][col];

            if (sMap[row][col] == 9)
            {
                babyShark.Pos.Row = row;
                babyShark.Pos.Col = col;

                sMap[row][col] = 0;
            }
        }
    }

    unsigned int time = 0;
    while (true)
    {
        Position eatableFish;
        unsigned int moveCount = GetShortestDistanceFish(babyShark, &eatableFish);

        if (moveCount == 0)
        {
            break;
        }

        ++babyShark.FishAteCount;
        if (babyShark.FishAteCount == babyShark.Size)
        {
            ++babyShark.Size;
            babyShark.FishAteCount = 0;
        }

        babyShark.Pos.Row = eatableFish.Row;
        babyShark.Pos.Col = eatableFish.Col;

        sMap[eatableFish.Row][eatableFish.Col] = 0;
        
        time += moveCount;
    }

    std::cout << time;

    return 0;
}