
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
    void Move(Shark* outBiggestSharkOrNullsMap[][MAX_MAP_SIZE]);

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

// Sets on map only if this shark is bigger than other shark
void Shark::Move(Shark* outBiggestSharkOrNullsMap[][MAX_MAP_SIZE])
{
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
    default:
        assert(false);
        break;
    }


    Shark* otherSharkOrNull = outBiggestSharkOrNullsMap[CurrentPosition.Row][CurrentPosition.Column];
    if (otherSharkOrNull != nullptr)
    {
        if (Size < otherSharkOrNull->Size)
        {
            bAlive = false;
            return;
        }

        otherSharkOrNull->bAlive = false;
    }

    outBiggestSharkOrNullsMap[CurrentPosition.Row][CurrentPosition.Column] = this;
}

class Fisher
{
public:
    Fisher();

    unsigned int GetCaughtSharksSize() const;
    unsigned int GetPositionColumn() const;
    void MovePositionColumn();
    bool CatchNearestRowShark(Shark* outSharkOrNullsMap[][MAX_MAP_SIZE]);

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

bool Fisher::CatchNearestRowShark(Shark* outSharkOrNullsMap[][MAX_MAP_SIZE])
{
    for (int row = 0; row < sMaxMapSizeRow; ++row)
    {
        if (outSharkOrNullsMap[row][mPositionColumn] != nullptr)
        {
            Shark* caughtShark = outSharkOrNullsMap[row][mPositionColumn];
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

    std::queue<Shark*> pSharkQueue;
    Shark* pSharkOrNullsMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = { nullptr, };

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
        
        pSharkQueue.push(&sharks.back());
        pSharkOrNullsMap[sharkPosition.Row][sharkPosition.Column] = &sharks.back();
    }

    // Start fishing
    Fisher fisher;

    for (int fisherPositionColumn = fisher.GetPositionColumn(); fisherPositionColumn < sMaxMapSizeColumn; ++fisherPositionColumn)
    {
        fisher.CatchNearestRowShark(pSharkOrNullsMap);

        // Must reset map
        for (int row = 0; row < sMaxMapSizeRow; ++row)
        {
            for (int column = 0; column < sMaxMapSizeColumn; ++column)
            {
                pSharkOrNullsMap[row][column] = nullptr;
            }
        }

        unsigned int sharkQueueSize = static_cast<unsigned int>(pSharkQueue.size());
        for (unsigned int sharkIndex = 0; sharkIndex < sharkQueueSize; ++sharkIndex)
        {
            Shark* pShark = pSharkQueue.front();
            pSharkQueue.pop();
            if (pShark->bAlive == false)
            {
                continue;
            }

            pSharkQueue.push(pShark);

            // Set biggest shark on the map
            pShark->Move(pSharkOrNullsMap);
        }

        fisher.MovePositionColumn();
    }

    std::cout << fisher.GetCaughtSharksSize() << std::endl;
    
    return 0;
}