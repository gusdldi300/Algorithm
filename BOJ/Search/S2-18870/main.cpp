
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_COORDINATES_COUNT (1000001U)

int main()
{
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    unsigned int coordinatesCount;
    std::cin >> coordinatesCount;

    std::vector<int> coordinates;
    coordinates.reserve(MAX_COORDINATES_COUNT);

    std::vector<int> coordinatesAscend;
    coordinatesAscend.reserve(MAX_COORDINATES_COUNT);
    for (unsigned int i = 0; i < coordinatesCount; ++i)
    {
        int coordinate;
        std::cin >> coordinate;

        coordinates.push_back(coordinate);
        coordinatesAscend.push_back(coordinate);
    }

    std::sort(coordinatesAscend.begin(), coordinatesAscend.end());

    std::vector<int> uniqueCoordinatesAscend;
    uniqueCoordinatesAscend.reserve(MAX_COORDINATES_COUNT);

    int lastCoordinate = coordinatesAscend[0];
    uniqueCoordinatesAscend.push_back(lastCoordinate);

    for (unsigned int i = 1; i < coordinatesAscend.size(); ++i)
    {
        int coordinate = coordinatesAscend[i];
        if (coordinate != lastCoordinate)
        {
            uniqueCoordinatesAscend.push_back(coordinate);
        }

        lastCoordinate = coordinate;
    }

    for (unsigned int i = 0; i < coordinates.size(); ++i)
    {
        int findCoordinate = coordinates[i];

        // Binary search
        int foundIndex = 0;

        int startIndex = 0;
        int endIndex = uniqueCoordinatesAscend.size() - 1;

        while (startIndex <= endIndex)
        {
            int midIndex = (startIndex + endIndex) / 2;
            if (findCoordinate == uniqueCoordinatesAscend[midIndex])
            {
                foundIndex = midIndex;
                break;
            }

            if (findCoordinate < uniqueCoordinatesAscend[midIndex])
            {
                endIndex = midIndex - 1;
            }
            else
            {
                startIndex = midIndex + 1;
            }
        }

        std::cout << foundIndex << ' ';
    }

    return 0;
}