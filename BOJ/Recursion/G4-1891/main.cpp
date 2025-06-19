
#include <cassert>
#include <iostream>
#include <string>
#include <cmath>

struct Position
{
    long long x;
    long long y;
};

void TransformFragmentNumberToPositionRecursive(Position& startPosition, Position& endPosition, const Position& movePosition, int fragmentNumberIndex, const int fragmentNumberDigits, const std::string& fragmentNumber, Position* outTransformedPosition)
{
    if (fragmentNumberDigits == fragmentNumberIndex)
    {
        outTransformedPosition->x = startPosition.x;
        outTransformedPosition->y = startPosition.y;

        return;
    }

    long long sideLength = endPosition.x - startPosition.x + 1;
    long long positionOffset = sideLength / 2;

    int side = fragmentNumber[fragmentNumberIndex] - '0';
    switch (side)
    {
    case 1:
        startPosition.x += positionOffset;
        endPosition.y -= positionOffset;
        
        break;
    case 2:
        endPosition.x -= positionOffset;
        endPosition.y -= positionOffset;

        break;
    case 3:
        startPosition.y += positionOffset;
        endPosition.x -= positionOffset;

        break;
    case 4:
        startPosition.x += positionOffset;
        startPosition.y += positionOffset;

        break;
    default:
        assert(false);
        break;
    }

    TransformFragmentNumberToPositionRecursive(startPosition, endPosition, movePosition, fragmentNumberIndex + 1, fragmentNumberDigits, fragmentNumber, outTransformedPosition);
}

void TransformPositionToFragmentNumberRecursive(Position& startPosition, Position& endPosition, const Position& transformedPosition, const int fragmentNumberDigits, std::string* outFragmentNumber)
{
    if (outFragmentNumber->size() == fragmentNumberDigits)
    {
        return;
    }

    long long sideLength = endPosition.x - startPosition.x + 1;
    long long positionOffset = sideLength / 2;

    Position centerPosition = { endPosition.x - positionOffset, endPosition.y - positionOffset };
    if (transformedPosition.x > centerPosition.x)
    {
        if (transformedPosition.y <= centerPosition.y)
        {
            outFragmentNumber->append("1");
            startPosition.x += positionOffset;
            endPosition.y -= positionOffset;
        }
        else
        {
            outFragmentNumber->append("4");
            startPosition.x += positionOffset;
            startPosition.y += positionOffset;
        }
    }
    else
    {
        if (transformedPosition.y <= centerPosition.y)
        {
            outFragmentNumber->append("2");
            endPosition.x -= positionOffset;
            endPosition.y -= positionOffset;
        }
        else
        {
            outFragmentNumber->append("3");
            startPosition.y += positionOffset;
            endPosition.x -= positionOffset;
        }
    }

    TransformPositionToFragmentNumberRecursive(startPosition, endPosition, transformedPosition, fragmentNumberDigits, outFragmentNumber);
}


int main()
{
    int fragmentNumberDigits = 0;
    std::string fragmentNumber;

    std::cin >> fragmentNumberDigits >> fragmentNumber;
    
    Position movePosition;
    std::cin >> movePosition.x >> movePosition.y;
    movePosition.y = -movePosition.y;

    //long long maxCoordinate = pow(2.0, fragmentNumberDigits) - 1;
    long long maxCoordinate = (1LL << fragmentNumberDigits) - 1;
    
    Position startPosition = { 0, 0 };
    Position endPosition = { maxCoordinate, maxCoordinate };

    Position transformedPosition = { 0, 0 };
    TransformFragmentNumberToPositionRecursive(startPosition, endPosition, movePosition, 0, fragmentNumberDigits, fragmentNumber, &transformedPosition);

    transformedPosition.x += movePosition.x;
    transformedPosition.y += movePosition.y;
    if (transformedPosition.x < 0 || transformedPosition.x > maxCoordinate || transformedPosition.y < 0 || transformedPosition.y > maxCoordinate)
    {
        std::cout << -1;
        
        return 0;
    }

    startPosition.x = 0;
    startPosition.y = 0;

    endPosition.x = maxCoordinate;
    endPosition.y = maxCoordinate;

    std::string transformedFragmentNumber;
    transformedFragmentNumber.reserve(fragmentNumberDigits);
    TransformPositionToFragmentNumberRecursive(startPosition, endPosition, transformedPosition, fragmentNumberDigits, &transformedFragmentNumber);
    
    std::cout << transformedFragmentNumber;

    return 0;
}
