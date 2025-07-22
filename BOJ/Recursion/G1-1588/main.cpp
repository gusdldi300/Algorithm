
#include <cassert>
#include <cmath>
#include <iostream>

class NumberCount
{
public:
    NumberCount();
    NumberCount(unsigned int one, unsigned int two, unsigned int three);
    virtual ~NumberCount() = default;

    void operator=(const NumberCount& other);
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

void NumberCount::operator=(const NumberCount& other)
{
    One = other.One;
    Two = other.Two;
    Three = other.Three;
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
unsigned int AddNumberCountRecursive(unsigned int startIndex, unsigned int number, unsigned int calcTime, const unsigned int totalCount, NumberCount* outNumberCount)
{
    if (calcTime == 0)
    {
        *outNumberCount += sNumberCounts[calcTime][number - 1];

        return 1;
    }

    unsigned int currentCount = static_cast<unsigned int>(pow(3.0, calcTime));
    if ((startIndex % currentCount == 0) && (currentCount <= totalCount))
    {
        *outNumberCount += sNumberCounts[calcTime][number - 1];

        return currentCount;
    }

    unsigned int prevCount = static_cast<unsigned int>(pow(3.0, calcTime - 1));
    unsigned int prevNumber = sTransformedNumbers[number - 1][startIndex / prevCount] - '0';

    return AddNumberCountRecursive(startIndex % prevCount, prevNumber, calcTime - 1, totalCount, outNumberCount);
}

int main()
{
    unsigned int calcTime = 0;
    unsigned int left = 0;
    unsigned int right = 0;

    std::cin >> sFirstNumber >> left >> right >> calcTime;

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

    while (startIndex <= endIndex)
    {
        unsigned int readCount = AddNumberCountRecursive(startIndex, sFirstNumber, calcTime, endIndex - startIndex + 1, &numberCount);
        startIndex += readCount;
    }

    std::cout << numberCount.One << ' ' << numberCount.Two << ' ' << numberCount.Three;

    return 0;
}