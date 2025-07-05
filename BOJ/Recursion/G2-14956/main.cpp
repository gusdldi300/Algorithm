
#include <cassert>
#include <iostream>

#define MAX_PATH_COUNT (4)
#define MIN_SQUARE_LENGTH (1)

enum class ePathDirection : unsigned int
{
    Up = 0,
    Down,
    Left,
    Right
};

struct Path
{
    ePathDirection Direction;
    unsigned int Quadrant;
};

static unsigned int sStepCount = 0;
static unsigned int sSquareLength = 0;
// Up, Down, Left, Right
static const Path sPrevPaths[MAX_PATH_COUNT][MAX_PATH_COUNT] =
{
    { { ePathDirection::Right, 1 }, { ePathDirection::Up, 2 }, { ePathDirection::Up, 3 }, { ePathDirection::Left, 4 }, },
    { { ePathDirection::Left, 3 }, { ePathDirection::Down, 4 }, { ePathDirection::Down, 1 }, { ePathDirection::Right, 2 }, },
    { { ePathDirection::Down, 3 }, { ePathDirection::Left, 2 }, { ePathDirection::Left, 1 }, { ePathDirection::Up, 4 }, },
    { { ePathDirection::Up, 1 }, { ePathDirection::Right, 4 }, { ePathDirection::Right, 3 }, { ePathDirection::Down, 2 }, }
};

void PrintPhilosoperPositionRecursive(ePathDirection pathDirection, unsigned int leftStepCount, unsigned int x, unsigned int y, unsigned int squareLength)
{
    if (squareLength <= MIN_SQUARE_LENGTH)
    {
        std::cout << x << ' ' << y;
        
        return;
    }

    unsigned int quadrantStepOffset = (squareLength * squareLength) / 4;
    unsigned int quadrantStepCount = 0;

    unsigned int pathsIndex = 0;
    for (pathsIndex = 0; pathsIndex < MAX_PATH_COUNT; ++pathsIndex)
    {
        quadrantStepCount += quadrantStepOffset;

        if (leftStepCount <= quadrantStepCount)
        {
            break;
        }
    }

    Path path = sPrevPaths[static_cast<unsigned int>(pathDirection)][pathsIndex];

    unsigned int qaudrantOffset = squareLength / 2;
    unsigned int prevX = x;
    unsigned int prevY = y;
    switch (path.Quadrant)
    {
    case 1:
        // Do nothing;
        break;
    case 2:
        prevY += qaudrantOffset;

        break;
    case 3:
        prevX += qaudrantOffset;
        prevY += qaudrantOffset;

        break;
    case 4:
        prevX += qaudrantOffset;

        break;
    default:
        assert(false);
        break;
    }

    PrintPhilosoperPositionRecursive(path.Direction, leftStepCount - (quadrantStepCount - quadrantStepOffset), prevX, prevY, qaudrantOffset);
}

int main()
{
    std::cin >> sSquareLength >> sStepCount;

    PrintPhilosoperPositionRecursive(ePathDirection::Up, sStepCount, 1, 1, sSquareLength);

    return 0;
}