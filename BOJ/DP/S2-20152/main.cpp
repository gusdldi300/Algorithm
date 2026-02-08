
#include <iostream>

#define MAX_MAP_SIZE (30)

static unsigned int sPaths[MAX_MAP_SIZE + 1][MAX_MAP_SIZE + 1] = { 0, };

int main()
{
    int home = 0;
    int pcRoom = 0;

    std::cin >> home >> pcRoom;

    if (home == pcRoom)
    {
        std::cout << 1;

        return 0;
    }

    int startPosition = home;
    int endPosition = pcRoom;

    if (home > pcRoom)
    {
        startPosition = pcRoom;
        endPosition = home;
    }

    sPaths[startPosition][startPosition] = 1;
    for (int row = startPosition; row <= endPosition; ++row)
    {
        for (int col = row; col <= endPosition; ++col)
        {
            
        }
    }

    return 0;
}