
#include <iostream>
#include <queue>
#include <unordered_set>
#include <cassert>

#define MAX_BOARD_SIZE_ROW (6)
#define MAX_BOARD_SIZE_COL (6)

#define MAX_CUBE_NET_SIZE (3U)
#define MAX_MOVE_DIRECTIONS_SIZE (4U)
#define CUBE_SIDES_SIZE (6U)

#define NET_ROW_SIZE (4U)
#define NET_COL_SIZE (3U)

#define NET_BUTTOM_SIDE_INDEX (1U)

enum class eDirection : unsigned int
{
    North = 0,
    East,
    South,
    West
};

enum class eSide : unsigned int
{
    Top = 0,
    Buttom,
    Up,
    Right,
    Down,
    Left
};

struct Position
{
    int Row;
    int Col;
};

struct Net
{
    eSide RowSides[NET_ROW_SIZE] = { eSide::Left, eSide::Buttom, eSide::Right, eSide::Top };
    eSide ColSides[NET_COL_SIZE] = { eSide::Up, eSide::Buttom, eSide::Down };
};

static const Position MOVE_DIRECTIONS[MAX_MOVE_DIRECTIONS_SIZE] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

static void DiscriminateNetCubeRecursive(int row, int col, Net cubeNet, std::unordered_set<eSide>& cubeNetDiscriminator, bool board[][MAX_BOARD_SIZE_COL], bool visited[][MAX_BOARD_SIZE_COL])
{
    for (unsigned int dirIndex = 0; dirIndex < MAX_MOVE_DIRECTIONS_SIZE; ++dirIndex)
    {
        int nextRow = row + MOVE_DIRECTIONS[dirIndex].Row;
        int nextCol = col + MOVE_DIRECTIONS[dirIndex].Col;

        if (nextRow < 0 || nextRow >= MAX_BOARD_SIZE_ROW ||
            nextCol < 0 || nextCol >= MAX_BOARD_SIZE_COL)
        {
            continue;
        }

        if (board[nextRow][nextCol] == 0 || visited[nextRow][nextCol])
        {
            continue;
        }

        eDirection moveDirection = static_cast<eDirection>(dirIndex);
        Net nextCubeNet = cubeNet;

        eSide tempSide;
        switch (moveDirection)
        {
        case eDirection::North:
            tempSide = nextCubeNet.ColSides[2];

            nextCubeNet.ColSides[2] = nextCubeNet.ColSides[1];
            nextCubeNet.ColSides[1] = nextCubeNet.ColSides[0];
            nextCubeNet.ColSides[0] = nextCubeNet.RowSides[3];
            nextCubeNet.RowSides[3] = tempSide;

            nextCubeNet.RowSides[NET_BUTTOM_SIDE_INDEX] = nextCubeNet.ColSides[NET_BUTTOM_SIDE_INDEX];

            break;
        case eDirection::East:
            tempSide = nextCubeNet.RowSides[0];

            nextCubeNet.RowSides[0] = nextCubeNet.RowSides[1];
            nextCubeNet.RowSides[1] = nextCubeNet.RowSides[2];
            nextCubeNet.RowSides[2] = nextCubeNet.RowSides[3];
            nextCubeNet.RowSides[3] = tempSide;

            nextCubeNet.ColSides[NET_BUTTOM_SIDE_INDEX] = nextCubeNet.RowSides[NET_BUTTOM_SIDE_INDEX];

            break;
        case eDirection::South:
            tempSide = nextCubeNet.ColSides[0];

            nextCubeNet.ColSides[0] = nextCubeNet.ColSides[1];
            nextCubeNet.ColSides[1] = nextCubeNet.ColSides[2];
            nextCubeNet.ColSides[2] = nextCubeNet.RowSides[3];
            nextCubeNet.RowSides[3] = tempSide;

            nextCubeNet.RowSides[NET_BUTTOM_SIDE_INDEX] = nextCubeNet.ColSides[NET_BUTTOM_SIDE_INDEX];

            break;
        case eDirection::West:
            tempSide = nextCubeNet.RowSides[3];

            nextCubeNet.RowSides[3] = nextCubeNet.RowSides[2];
            nextCubeNet.RowSides[2] = nextCubeNet.RowSides[1];
            nextCubeNet.RowSides[1] = nextCubeNet.RowSides[0];
            nextCubeNet.RowSides[0] = tempSide;

            nextCubeNet.ColSides[NET_BUTTOM_SIDE_INDEX] = nextCubeNet.RowSides[NET_BUTTOM_SIDE_INDEX];

            break;
        default:
            assert(false);
            break;
        }

        visited[nextRow][nextCol] = true;
        cubeNetDiscriminator.insert(nextCubeNet.RowSides[NET_BUTTOM_SIDE_INDEX]);

        DiscriminateNetCubeRecursive(nextRow, nextCol, nextCubeNet, cubeNetDiscriminator, board, visited);
    }
}

int main()
{
    bool board[MAX_CUBE_NET_SIZE][MAX_BOARD_SIZE_ROW][MAX_BOARD_SIZE_COL] = { false, };

    for (unsigned int cubeNetIndex = 0; cubeNetIndex < MAX_CUBE_NET_SIZE; ++cubeNetIndex)
    {
        for (int row = 0; row < MAX_BOARD_SIZE_ROW; ++row)
        {
            for (int col = 0; col < MAX_BOARD_SIZE_COL; ++col)
            {
                int state = 0;
                std::cin >> state;

                board[cubeNetIndex][row][col] = static_cast<bool>(state);
            }
        }
    }

    for (unsigned int cubeNetIndex = 0; cubeNetIndex < MAX_CUBE_NET_SIZE; ++cubeNetIndex)
    {
        bool visited[MAX_BOARD_SIZE_ROW][MAX_BOARD_SIZE_COL] = { false, };

        for (int row = 0; row < MAX_BOARD_SIZE_ROW; ++row)
        {
            for (int col = 0; col < MAX_BOARD_SIZE_COL; ++col)
            {
                if (board[cubeNetIndex][row][col] == false || visited[row][col])
                {
                    continue;
                }

                std::unordered_set<eSide> cubeNetDiscriminator;
                cubeNetDiscriminator.insert(eSide::Buttom);

                visited[row][col] = true;
                Net cubeNet;

                DiscriminateNetCubeRecursive(row, col, cubeNet, cubeNetDiscriminator, board[cubeNetIndex], visited);

                if (cubeNetDiscriminator.size() == CUBE_SIDES_SIZE)
                {
                    std::cout << "yes" << std::endl;

                    continue;
                }

                std::cout << "no" << std::endl;
            }
        }
    }
    
    return 0;
}
