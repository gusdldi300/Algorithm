
#include <cassert>
#include <iostream>

class NumberCount
{
public:
    NumberCount();
    NumberCount(unsigned int one, unsigned int two, unsigned int three);
    virtual ~NumberCount() = default;

    NumberCount operator+(const NumberCount& other) const;
    NumberCount& operator+=(const NumberCount& other);

public:
    unsigned int One;
    unsigned int Two;
    unsigned int Three;
};

NumberCount::NumberCount()
    : One(0)
    , Two(0)
    , Three(0)
{
}

NumberCount::NumberCount(unsigned int one, unsigned int two, unsigned int three)
    : One(one)
    , Two(two)
    , Three(three)
{
}

NumberCount NumberCount::operator+(const NumberCount& other) const
{
    NumberCount numberCount(One + other.One, Two + other.Two, Three + other.Three);

    return numberCount;
}

NumberCount& NumberCount::operator+=(const NumberCount& other)
{
    One += other.One;
    Two += other.Two;
    Three += other.Three;

    return *this;
}

#define MAX_CALC_TIME (21)
#define MAX_NUMBER (3)

static NumberCount sNumberCounts[MAX_CALC_TIME][MAX_NUMBER];
static const std::string sTransformedNumbers[MAX_NUMBER] = { "132", "211", "232" };
static unsigned int sFirstNumber = 0;

// Returns transformed number
unsigned int GetNumberCountRecursive(unsigned int index, unsigned int calcTime)
{
    if (calcTime == 0)
    {
        return sFirstNumber;
    }

    unsigned int currentIndex = index % (unsigned int)(pow(3.0, calcTime));
    unsigned prevIndex = currentIndex / (unsigned int)(pow(3.0, calcTime - 1));

    unsigned int transformedNumber = GetNumberCountRecursive(prevIndex, calcTime - 1);

    return sTransformedNumbers[transformedNumber - 1][currentIndex % MAX_NUMBER] - '0';
}

int main()
{
    unsigned int firstNumber = 0;
    unsigned int calcTime = 0;
    unsigned int left = 0;
    unsigned int right = 0;

    std::cin >> sFirstNumber >> left >> right >> calcTime;
    std::cin >> firstNumber >> left >> right >> calcTime;

    sNumberCounts[0][0] = { 1, 0, 0 };
    sNumberCounts[0][1] = { 0, 1, 0 };
    sNumberCounts[0][2] = { 0, 0, 1 };

    for (unsigned int row = 1; row <= calcTime; ++row)
    {
        unsigned int prevRow = row - 1;

        sNumberCounts[row][0] = sNumberCounts[prevRow][0] + sNumberCounts[prevRow][2] + sNumberCounts[prevRow][1];
        sNumberCounts[row][1] = sNumberCounts[prevRow][1] + sNumberCounts[prevRow][0] + sNumberCounts[prevRow][0];
        sNumberCounts[row][2] = sNumberCounts[prevRow][1] + sNumberCounts[prevRow][2] + sNumberCounts[prevRow][1];
    }

    unsigned int startIndex = left;
    unsigned int endIndex = right;

    NumberCount numberCount;
    while (startIndex > endIndex)
    {
        bool bFound = false;
        for (int time = static_cast<int>(calcTime); time >= 0; --time)
        {
            unsigned int calcTimeCount = pow(3.0, calcTime);

            if ((startIndex % calcTimeCount == 0) && ((endIndex - startIndex) < calcTimeCount))
            {
                numberCount += sNumberCounts[firstNumber][calcTime];
                startIndex += calcTimeCount;

                bFound = true;

                break;
            }
        }

        if (bFound)
        {
            continue;
        }

        unsigned int transformedNumber = GetNumberCountRecursive(startIndex, calcTime);
        switch (transformedNumber)
        {
        case 1:
            numberCount.One++;
            break;
        case 2:
            numberCount.Two++;
            break;
        case 3:
            numberCount.Three++;
            break;
        default:
            assert(false);
            break;
        }

        startIndex++;
    }

    std::cout << numberCount.One << ' ' << numberCount.Two << ' ' << numberCount.Three;

    return 0;
}