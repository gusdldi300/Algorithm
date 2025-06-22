
#include <cassert>
#include <cmath>
#include <iostream>

struct Position
{
    unsigned int row;
    unsigned int col;
};

static unsigned int sOuterBoxCount;
static unsigned int sInnerBoxCount;
static unsigned int sInnerBoxStartOffset;

void PrintBoxColorRecursive(Position startPosition, unsigned int unitBoxLength, const Position& printPosition)
{
    if (unitBoxLength < 1)
    {
        std::cout << '0';

        return;
    }

    Position innerBoxStartPosition;
    innerBoxStartPosition.row = startPosition.row + (sInnerBoxStartOffset * unitBoxLength);
    innerBoxStartPosition.col = startPosition.col + (sInnerBoxStartOffset * unitBoxLength);

    unsigned int innerBoxLength = unitBoxLength * sInnerBoxCount;
    if ((printPosition.row >= innerBoxStartPosition.row && printPosition.row < (innerBoxStartPosition.row + innerBoxLength))
        && (printPosition.col >= innerBoxStartPosition.col && printPosition.col < (innerBoxStartPosition.col + innerBoxLength)))
    {
        std::cout << '1';

        return;
    }

    Position checkStartPosition;
    for (unsigned int rowCount = 0; rowCount < sOuterBoxCount; ++rowCount)
    {
        checkStartPosition.row = startPosition.row + (unitBoxLength * rowCount);
        for (unsigned int colCount = 0; colCount < sOuterBoxCount; ++colCount)
        {
            checkStartPosition.col = startPosition.col + (unitBoxLength * colCount);
            
            if ((printPosition.row >= checkStartPosition.row && printPosition.row < (checkStartPosition.row + unitBoxLength))
                && (printPosition.col >= checkStartPosition.col && printPosition.col < (checkStartPosition.col + unitBoxLength)))
            {
                goto area_found;
            }
        }
    }

    assert(false);

area_found:
    PrintBoxColorRecursive(checkStartPosition, unitBoxLength / sOuterBoxCount, printPosition);
}


int main()
{
    unsigned int time = 0;
    
    Position printStartPosition;
    Position printEndPosition;

    std::cin >> time >> sOuterBoxCount >> sInnerBoxCount
        >> printStartPosition.row >> printEndPosition.row
        >> printStartPosition.col >> printEndPosition.col;

    assert(time <= 10);
    assert(sOuterBoxCount >= 3 && sOuterBoxCount <= 8);
    assert(sInnerBoxCount >= 1 && sInnerBoxCount <= sOuterBoxCount - 2);
    assert((sOuterBoxCount - sInnerBoxCount) % 2 == 0);

    unsigned int maxPrintPosition = (unsigned int)(pow(sOuterBoxCount, time)) - 1;
    assert(printStartPosition.row <= maxPrintPosition && printStartPosition.col <= maxPrintPosition);
    assert(printEndPosition.row <= maxPrintPosition && printEndPosition.col <= maxPrintPosition);

    sInnerBoxStartOffset = (sOuterBoxCount - sInnerBoxCount) / 2;

    Position startPosition = { 0, 0 };

    for (unsigned int row = printStartPosition.row; row <= printEndPosition.row; ++row)
    {
        for (unsigned int col = printStartPosition.col; col <= printEndPosition.col; ++col)
        {
            Position printPosition = { row, col };
            PrintBoxColorRecursive(startPosition, pow(sOuterBoxCount, time - 1), printPosition);
        }

        std::cout << std::endl;
    }

    return 0;
}