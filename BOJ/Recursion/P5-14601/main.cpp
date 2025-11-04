
#include <cassert>
#include <cmath>
#include <iostream>

enum eRotateCW
{
    Degree90,
    Degree180,
    Degree270,
    Degree360,
};

enum eDirection : unsigned int
{
    NorthWest = 0,
    NorthEast,
    SouthWest,
    SouthEast
};

struct Position
{
    int X;
    int Y;
};

#define MAX_TILES_LENGTH (128) // 2^7

static Position sDrainPosition;
static int sTiles[MAX_TILES_LENGTH][MAX_TILES_LENGTH] = { 0, };
static int sAddNumber = 1;
static int sFirstUpdateNumber = 1;
static int sNumberOfBlocks = 0;

static int sCacheTiles[MAX_TILES_LENGTH][MAX_TILES_LENGTH] = { 0, };
static eDirection sDirections[] = { NorthWest, NorthEast, SouthWest, SouthEast };

void UpdateRotatedTiles(int outDestTiles[][MAX_TILES_LENGTH], const Position& destStartPosition, unsigned int tilesLength, const int rotateTiles[][MAX_TILES_LENGTH], eRotateCW rotateDegree, int addNumber, int firstUpdateNumber)
{
    assert(outDestTiles != nullptr);
    assert(tilesLength > 0);

    int tilesLengthInt = static_cast<int>(tilesLength);

    int destCol = 0;
    int destRow = 0;

    switch (rotateDegree)
    {
    case Degree90:
        destCol = destStartPosition.X + tilesLengthInt - 1;
        for (int row = 0; row < tilesLengthInt; ++row)
        {
            destRow = destStartPosition.Y;
            for (int col = 0; col < tilesLengthInt; ++col)
            {
                if (rotateTiles[row][col] == 0)
                {
                    outDestTiles[destRow][destCol] = firstUpdateNumber;
                }
                else
                {
                    outDestTiles[destRow][destCol] = rotateTiles[row][col] + addNumber;
                }

                destRow++;
            }

            destCol--;
        }

        break;
    case Degree180:
        destRow = destStartPosition.Y + tilesLengthInt - 1;
        for (int row = 0; row < tilesLengthInt; ++row)
        {
            destCol = destStartPosition.X + tilesLengthInt - 1;
            for (int col = 0; col < tilesLengthInt; ++col)
            {
                if (rotateTiles[row][col] == 0)
                {
                    outDestTiles[destRow][destCol] = firstUpdateNumber;
                }
                else
                {
                    outDestTiles[destRow][destCol] = rotateTiles[row][col] + addNumber;
                }

                destCol--;
            }

            destRow--;
        }

        break;
    case Degree270:
        destCol = destStartPosition.X;
        for (int row = 0; row < tilesLengthInt; ++row)
        {
            destRow = destStartPosition.Y + tilesLengthInt - 1;
            for (int col = 0; col < tilesLengthInt; ++col)
            {
                if (rotateTiles[row][col] == 0)
                {
                    outDestTiles[destRow][destCol] = firstUpdateNumber;
                }
                else
                {
                    outDestTiles[destRow][destCol] = rotateTiles[row][col] + addNumber;
                }

                destRow--;
            }

            destCol++;
        }

        break;
    case Degree360:
        destRow = destStartPosition.Y;
        for (int row = 0; row < tilesLengthInt; ++row)
        {
            destCol = destStartPosition.X;
            for (int col = 0; col < tilesLengthInt; ++col)
            {
                if (rotateTiles[row][col] == 0)
                {
                    outDestTiles[destRow][destCol] = firstUpdateNumber;
                }
                else
                {
                    outDestTiles[destRow][destCol] = rotateTiles[row][col] + addNumber;
                }

                destCol++;
            }

            destRow++;
        }

        break;
    default:
        assert(false);

        break;
    }
}

void FillNumbersToTilesRecursive(Position startPosition, eDirection direction, int tilesLength)
{
    // Search drain position
    if (tilesLength == 1 && (sDrainPosition.X == startPosition.X && sDrainPosition.Y == startPosition.Y))
    {
        sTiles[startPosition.Y][startPosition.X] = -1;

        return;
    }

    int halfLength = tilesLength / 2;
    
    Position nextPosition;
    eDirection nextDirection;
    if (sDrainPosition.X >= startPosition.X && sDrainPosition.X < startPosition.X + halfLength &&
        sDrainPosition.Y >= startPosition.Y && sDrainPosition.Y < startPosition.Y + halfLength)
    {
        nextPosition = startPosition;
        nextDirection = eDirection::NorthWest;
    }
    else if (sDrainPosition.X >= startPosition.X + halfLength && sDrainPosition.X < startPosition.X + tilesLength &&
        sDrainPosition.Y >= startPosition.Y && sDrainPosition.Y < startPosition.Y + halfLength)
    {
        nextPosition.X = startPosition.X + halfLength;
        nextPosition.Y = startPosition.Y;

        nextDirection = eDirection::NorthEast;
    }
    else if (sDrainPosition.X >= startPosition.X && sDrainPosition.X < startPosition.X + halfLength &&
        sDrainPosition.Y >= startPosition.Y + halfLength && sDrainPosition.Y < startPosition.Y + tilesLength)
    {
        nextPosition.X = startPosition.X;
        nextPosition.Y = startPosition.Y + halfLength;

        nextDirection = eDirection::SouthWest;
    }
    else
    {
        nextPosition.X = startPosition.X + halfLength;
        nextPosition.Y = startPosition.Y + halfLength;

        nextDirection = eDirection::SouthEast;
    }

    FillNumbersToTilesRecursive(nextPosition, nextDirection, tilesLength / 2);

    // Fill tiles with numbers
    for (eDirection checkDirection : sDirections)
    {
        if (nextDirection == checkDirection)
        {
            continue;
        }

        switch (checkDirection)
        {
        case NorthEast:
            UpdateRotatedTiles(sTiles, { startPosition.X + halfLength, startPosition.Y }, halfLength, sCacheTiles, eRotateCW::Degree270, sAddNumber, sFirstUpdateNumber);
            break;
        case NorthWest:
            UpdateRotatedTiles(sTiles, { startPosition.X, startPosition.Y }, halfLength, sCacheTiles, eRotateCW::Degree180, sAddNumber, sFirstUpdateNumber);
            break;
        case SouthEast:
            UpdateRotatedTiles(sTiles, { startPosition.X + halfLength, startPosition.Y + halfLength }, halfLength, sCacheTiles, eRotateCW::Degree360, sAddNumber, sFirstUpdateNumber);
            break;
        case SouthWest:
            UpdateRotatedTiles(sTiles, { startPosition.X, startPosition.Y + halfLength }, halfLength, sCacheTiles, eRotateCW::Degree90, sAddNumber, sFirstUpdateNumber);
            break;
        default:
            assert(false);
            break;
        }

        sAddNumber += sNumberOfBlocks;
    }

    sNumberOfBlocks = (sNumberOfBlocks * 4) + 1;
    sFirstUpdateNumber = sNumberOfBlocks + 1;
    sAddNumber++;
}

int main()
{
    unsigned int twosPower = 0;

    std::cin >> twosPower;
    std::cin >> sDrainPosition.X >> sDrainPosition.Y;
    
    unsigned int tilesLength = pow(2.0, twosPower);

    // Transform position
    sDrainPosition.X--;
    sDrainPosition.Y = tilesLength - sDrainPosition.Y;

    assert(sDrainPosition.X >= 0 && sDrainPosition.X < tilesLength);
    assert(sDrainPosition.Y >= 0 && sDrainPosition.Y < tilesLength);

    // CopyRotatedTiles() tests
    /*
    sCacheTiles[0][0] = 1;
    sCacheTiles[0][1] = 2;
    sCacheTiles[1][0] = 3;
    sCacheTiles[1][1] = 4;

    CopyRotatedTiles(sCacheTiles, { 2, 0 }, 2, sCacheTiles, eRotateCW::Degree270);
    CopyRotatedTiles(sCacheTiles, { 2, 2 }, 2, sCacheTiles, eRotateCW::Degree360);
    CopyRotatedTiles(sCacheTiles, { 0, 2 }, 2, sCacheTiles, eRotateCW::Degree90);

    CopyRotatedTiles(sCacheTiles, { 4, 4 }, 2, sCacheTiles, eRotateCW::Degree180);
    */

    sCacheTiles[0][0] = 0;

    int firstUpdateNumber = 1;
    int numberOfBlocks = 0;
    int addNumber = 1;
    for (unsigned int i = 0; i < twosPower; ++i)
    {
        int currentTilesLength = pow(2.0, i);

        UpdateRotatedTiles(sCacheTiles, { currentTilesLength, 0 }, currentTilesLength, sCacheTiles, eRotateCW::Degree270, addNumber, firstUpdateNumber);
        addNumber += numberOfBlocks;
        UpdateRotatedTiles(sCacheTiles, { currentTilesLength, currentTilesLength }, currentTilesLength, sCacheTiles, eRotateCW::Degree360, addNumber, firstUpdateNumber);
        addNumber += numberOfBlocks;
        UpdateRotatedTiles(sCacheTiles, { 0, currentTilesLength }, currentTilesLength, sCacheTiles, eRotateCW::Degree90, addNumber, firstUpdateNumber);
        addNumber += numberOfBlocks;

        numberOfBlocks = (numberOfBlocks * 4) + 1;
        firstUpdateNumber = numberOfBlocks + 1;
        addNumber++;
    }

    FillNumbersToTilesRecursive({ 0, 0 }, eDirection::NorthWest, tilesLength);

    for (unsigned int row = 0; row < tilesLength; ++row)
    {
        for (unsigned int col = 0; col < tilesLength; ++col)
        {
            std::cout << sTiles[row][col] << ' ';
        }
     
        std::cout << std::endl;
    }

    return 0;
}