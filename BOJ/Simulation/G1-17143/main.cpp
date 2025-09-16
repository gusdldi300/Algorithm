
#include <cassert>
#include <iostream>
#include <stack>
#include <queue>

#define MAX_MAP_SIZE (100)

int sMaxMapSizeRow = -1;
int sMaxMapSizeColumn = -1;
unsigned int sTotalSharkCount = -1;

struct Position
{
    int Row;
    int Column;
};

enum class eDirection
{
    Up = 1,
    Down,
    Right,
    Left
};

class Shark
{
public:
    Shark(const Position currentPosition, unsigned int size, unsigned int speed, eDirection moveDirection);
    void Move(std::queue<Shark*> outSharksMap[][MAX_MAP_SIZE]);

public:
    bool bAlive;
    Position CurrentPosition;
    unsigned int Size;
    unsigned int Speed;
    eDirection MoveDirection;
};

Shark::Shark(const Position currentPosition, unsigned int size, unsigned int speed, eDirection moveDirection)
    : bAlive(true)
    , CurrentPosition(currentPosition)
    , Size(size)
    , Speed(speed)
    , MoveDirection(moveDirection)
{
}

void Shark::Move(std::queue<Shark*> outSharksMap[][MAX_MAP_SIZE])
{
    Shark* pMoveShark = outSharksMap[CurrentPosition.Row][CurrentPosition.Column].front();
    outSharksMap[CurrentPosition.Row][CurrentPosition.Column].pop();

    int moveCount = -1;
    switch (MoveDirection)
    {
    case eDirection::Up:
    {
        moveCount = Speed - CurrentPosition.Row;
        if (moveCount <= 0)
        {
            CurrentPosition.Row = moveCount * -1;
            break;
        }

        // Determine direction
        int moveCountRemainder = moveCount % (sMaxMapSizeRow - 1); // down
        if ((moveCount / (sMaxMapSizeRow - 1)) % 2 == 0) 
        {
            if (moveCountRemainder == 0)
            {
                MoveDirection = eDirection::Up;
                CurrentPosition.Row = 0;
                
                break;
            }

            MoveDirection = eDirection::Down;
            CurrentPosition.Row = moveCountRemainder;
        }
        else
        {
            if (moveCountRemainder == 0)
            {
                MoveDirection = eDirection::Down;
                CurrentPosition.Row = (sMaxMapSizeRow - 1);

                break;
            }

            MoveDirection = eDirection::Up;
            CurrentPosition.Row = (sMaxMapSizeRow - 1) - moveCountRemainder;
        }

        break;
    }
    case eDirection::Down:
    {
        moveCount = Speed - (sMaxMapSizeRow - 1 - CurrentPosition.Row); // up
        if (moveCount <= 0)
        {
            CurrentPosition.Row += Speed;
            break;
        }

        int moveCountRemainder = moveCount % (sMaxMapSizeRow - 1);
        if ((moveCount / (sMaxMapSizeRow - 1)) % 2 == 0) 
        {
            if (moveCountRemainder == 0)
            {
                MoveDirection = eDirection::Down;
                CurrentPosition.Row = (sMaxMapSizeRow - 1);

                break;
            }

            MoveDirection = eDirection::Up;
            CurrentPosition.Row = (sMaxMapSizeRow - 1) - moveCountRemainder;
        }
        else
        {
            if (moveCountRemainder == 0)
            {
                MoveDirection = eDirection::Up;
                CurrentPosition.Row = 0;

                break;
            }

            MoveDirection = eDirection::Down;
            CurrentPosition.Row = moveCountRemainder;
        }

        break;
    }
    case eDirection::Left:
    {
        moveCount = CurrentPosition.Column - Speed; 
        if (moveCount >= 0)
        {
            CurrentPosition.Column = moveCount;
            break;
        }

        moveCount *= -1;
        int moveCountRemainder = moveCount % (sMaxMapSizeColumn -1); // right
        if ((moveCount / (sMaxMapSizeColumn - 1)) % 2 == 0)
        {
            if (moveCountRemainder == 0)
            {
                MoveDirection = eDirection::Left;
                CurrentPosition.Column = 0;

                break;
            }

            MoveDirection = eDirection::Right;
            CurrentPosition.Column = moveCountRemainder;
        }
        else
        {
            if (moveCountRemainder == 0)
            {
                MoveDirection = eDirection::Right;
                CurrentPosition.Column = (sMaxMapSizeColumn - 1);

                break;
            }

            MoveDirection = eDirection::Left;
            CurrentPosition.Column = (sMaxMapSizeColumn - 1) - moveCountRemainder;
        }

        break;
    }
    case eDirection::Right:
    {
        moveCount = Speed - (sMaxMapSizeColumn - 1 - CurrentPosition.Column);
        if (moveCount <= 0)
        {
            CurrentPosition.Column += Speed;
            break;
        }

        int moveCountRemainder = moveCount % (sMaxMapSizeColumn - 1); // left
        if ((moveCount / (sMaxMapSizeColumn - 1)) % 2 == 0)
        {
            if (moveCountRemainder == 0)
            {
                MoveDirection = eDirection::Right;
                CurrentPosition.Column = (sMaxMapSizeColumn - 1);

                break;
            }

            MoveDirection = eDirection::Left;
            CurrentPosition.Column = (sMaxMapSizeColumn - 1) - moveCountRemainder;
        }
        else
        {
            if (moveCountRemainder == 0)
            {
                MoveDirection = eDirection::Left;
                CurrentPosition.Column = 0;

                break;
            }

            MoveDirection = eDirection::Right;
            CurrentPosition.Column = moveCountRemainder;
        }

        break;
    }
    }

    outSharksMap[CurrentPosition.Row][CurrentPosition.Column].push(pMoveShark);
    std::queue<Shark*> checkQueue = outSharksMap[pMoveShark->CurrentPosition.Row][pMoveShark->CurrentPosition.Column];
}

class Fisher
{
public:
    Fisher();

    unsigned int GetCaughtSharksSize() const;
    unsigned int GetPositionColumn() const;
    void MovePositionColumn();
    bool CatchNearestRowShark(std::queue<Shark*> outSharkMap[][MAX_MAP_SIZE]);


private:
    std::vector<Shark*> mCaughtSharks;
    int mPositionColumn;
};

Fisher::Fisher()
    : mPositionColumn(0)
{
}

unsigned int Fisher::GetCaughtSharksSize() const
{
    unsigned int sharksSize = 0;
    for (const Shark* shark : mCaughtSharks)
    {
        sharksSize += shark->Size;
    }

    return sharksSize;
}

unsigned int Fisher::GetPositionColumn() const
{
    return mPositionColumn;
}

void Fisher::MovePositionColumn()
{
    mPositionColumn++;
}

bool Fisher::CatchNearestRowShark(std::queue<Shark*> outSharkMap[][MAX_MAP_SIZE])
{
    for (int row = 0; row < sMaxMapSizeRow; ++row)
    {
        if (outSharkMap[row][mPositionColumn].size() > 0)
        {
            Shark* caughtShark = outSharkMap[row][mPositionColumn].front();
            outSharkMap[row][mPositionColumn].pop();
            caughtShark->bAlive = false;
            
            mCaughtSharks.push_back(caughtShark);
            //std::cout << "Caught shark: " << caughtShark->Size << std::endl;

            return true;
        }
    }

    return false;
}

int main(void)
{
    enum
    {
        MAX_SHARK_COUNT = (MAX_MAP_SIZE * MAX_MAP_SIZE)
    };
    
    std::cin >> sMaxMapSizeRow >> sMaxMapSizeColumn >> sTotalSharkCount;
    assert(sMaxMapSizeRow <= MAX_MAP_SIZE && sMaxMapSizeColumn <= MAX_MAP_SIZE);
    assert(sTotalSharkCount <= MAX_SHARK_COUNT);
    
    std::queue<Shark> sharks;

    std::queue<Shark*> sharkQueue;
    std::queue<Shark*> sharksMap[MAX_MAP_SIZE][MAX_MAP_SIZE];

    for (unsigned int sharkIndex = 0; sharkIndex < sTotalSharkCount; ++sharkIndex)
    {
        Position sharkPosition = { 0, };
        unsigned int sharkSpeed = 0;
        unsigned int sharkMoveDirection = 0;
        unsigned int sharkSize = 0;

        std::cin >> sharkPosition.Row >> sharkPosition.Column 
            >> sharkSpeed >> sharkMoveDirection >> sharkSize;

        sharkPosition.Row--;
        sharkPosition.Column--;

        Shark newShark(sharkPosition, sharkSize, sharkSpeed, static_cast<eDirection>(sharkMoveDirection));
        sharks.push(newShark);
        
        sharkQueue.push(&sharks.back());
        sharksMap[sharkPosition.Row][sharkPosition.Column].push(&sharks.back());
    }

    // Start fishing
    Fisher fisher;

    for (int fisherPositionColumn = fisher.GetPositionColumn(); fisherPositionColumn < sMaxMapSizeColumn; ++fisherPositionColumn)
    {
        fisher.CatchNearestRowShark(sharksMap);

        // Move sharks
        unsigned int sharkQueueSize = static_cast<unsigned int>(sharkQueue.size());
        for (unsigned int sharkIndex = 0; sharkIndex < sharkQueueSize; ++sharkIndex)
        {
            Shark* pShark = sharkQueue.front();
            sharkQueue.pop();
            if (pShark->bAlive == false)
            {
                continue;
            }
            sharkQueue.push(pShark);

            pShark->Move(sharksMap);

            /*
            std::cout << pShark->Size << ": " << pShark->CurrentPosition.Row << ", " << pShark->CurrentPosition.Column << ", ";
            switch (pShark->MoveDirection)
            {
            case eDirection::Up:
                std::cout << "Up";
                break;
            case eDirection::Down:
                std::cout << "Down";
                break;
            case eDirection::Left:
                std::cout << "Left";
                break;
            case eDirection::Right:
                std::cout << "Right";
                break;
            default:
                assert(false);
                break;
            }

            std::cout << std::endl;
            */
        }
        //std::cout << std::endl;

        // Get biggest shark in every map
        for (int row = 0; row < sMaxMapSizeRow; ++row)
        {
            for (int column = 0; column < sMaxMapSizeColumn; ++column)
            {
                // Todo: Compare stack
                if (sharksMap[row][column].size() <= 1)
                {
                    continue;
                }

                Shark* pBiggestShark = sharksMap[row][column].front();
                sharksMap[row][column].pop();
                pBiggestShark->bAlive = false;

                while (sharksMap[row][column].empty() == false)
                {
                    Shark* pCompareShark = sharksMap[row][column].front();
                    if (pBiggestShark->Size < pCompareShark->Size)
                    {
                        pBiggestShark = pCompareShark;
                    }

                    sharksMap[row][column].pop();
                    pCompareShark->bAlive = false;
                }

                sharksMap[row][column].push(pBiggestShark);
                pBiggestShark->bAlive = true;
            }
        }

        fisher.MovePositionColumn();
    }

    std::cout << fisher.GetCaughtSharksSize() << std::endl;
    
    return 0;
}