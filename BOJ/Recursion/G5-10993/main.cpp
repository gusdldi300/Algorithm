#include <cassert>
#include <iostream>

#define MAX_CANVAS_ROW (2048)
#define MAX_CANVAS_COL (2048)

#define STAR ('*')
#define BLANK (' ')

void PrintStarRecursive(int turn, int startRow, int startCol, int currentHeight, int currentWidth, char canvas[][MAX_CANVAS_COL])
{
    if (turn == 1)
    {
        canvas[startRow][startCol] = STAR;

        return;
    }

    int endWidth = startCol + currentWidth;
    for (int drawCol = startCol; drawCol < endWidth; ++drawCol)
    {
        canvas[startRow][drawCol] = STAR;
    }
    
    int nextHeight = currentHeight / 2;
    int nextWidth = (nextHeight * 2) - 1;
    int nextRow = 0;

    int leftDrawCol = startCol + 1;
    int rightDrawCol = endWidth - 2;

    if ((turn % 2) != 0)
    {
        int endRow = startRow - currentHeight + 1;
        for (int drawRow = startRow - 1; drawRow >= endRow; --drawRow)
        {
            canvas[drawRow][leftDrawCol] = STAR;
            canvas[drawRow][rightDrawCol] = STAR;

            leftDrawCol++;
            rightDrawCol--;
        }

        nextRow = startRow - nextHeight;
    }
    else
    {
        int endRow = startRow + currentHeight - 1;
        for (int drawRow = startRow + 1; drawRow <= endRow; ++drawRow)
        {
            canvas[drawRow][leftDrawCol] = STAR;
            canvas[drawRow][rightDrawCol] = STAR;

            leftDrawCol++;
            rightDrawCol--;
        }

        nextRow = startRow + nextHeight;
    }

    PrintStarRecursive(turn - 1, nextRow, startCol + nextHeight + 1, nextHeight, nextWidth, canvas);
}

int GetHeightRecursive(int currentTurn, int height, int targetTurn)
{
    assert(targetTurn <= 10);

    if (targetTurn == 1)
    {
        return 1;
    }
    else if (targetTurn == 2)
    {
        return 3;
    }

    if (currentTurn == targetTurn)
    {
        return height;
    }

    return GetHeightRecursive(currentTurn + 1, height * 2 + 1, targetTurn);
}

int main()
{
    int turn = 0;
    std::cin >> turn;
    
    char canvas[MAX_CANVAS_ROW][MAX_CANVAS_COL];
    int currentHeight = GetHeightRecursive(1, 1, turn);
    int currentWidth = (currentHeight * 2) - 1;

    bool bTriangle = turn % 2 == 0 ? false : true;
    int blankWidth = 0;  bTriangle ? (currentWidth / 2) + 1 : currentWidth;

    if (bTriangle)
    {
        blankWidth = (currentWidth / 2) + 1;
        for (int row = 0; row < currentHeight; ++row)
        {
            for (int col = 0; col < blankWidth; ++col)
            {
                canvas[row][col] = BLANK;
            }

            blankWidth++;
        }

        PrintStarRecursive(turn, currentHeight - 1, 0, currentHeight, currentWidth, canvas);
    }
    else
    {
        blankWidth = currentWidth;
        for (int row = 0; row < currentHeight; ++row)
        {
            for (int col = 0; col < blankWidth; ++col)
            {
                canvas[row][col] = BLANK;
            }

            blankWidth--;
        }

        PrintStarRecursive(turn, 0, 0, currentHeight, currentWidth, canvas);
    }

    for (int row = 0; row < currentHeight; ++row)
    {
        for (int col = 0; col < currentWidth; ++col)
        {
            if (canvas[row][col] == STAR)
            {
                std::cout << STAR;
            }
            else if (canvas[row][col] == BLANK)
            {
                std::cout << BLANK;
            }
            else
            {
                break;
            }
        }

        std::cout << std::endl;
    }

    return 0;
}