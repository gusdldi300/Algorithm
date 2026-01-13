
#include <iostream>
#include <vector>

#define MAX_NAME_SIZE (2001U)
#define CHEMISTRY_POINT_COMPARE_COUNT (2U)

static unsigned int ALPHABET_STROKES[] = { 3, 2, 1, 2, 3, 3, 2, 3, 3, 2, 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 1, 1, 2, 2, 1 };

int main()
{
    std::string firstPerson;
    firstPerson.reserve(MAX_NAME_SIZE);
    std::string secondPerson;
    secondPerson.reserve(MAX_NAME_SIZE);

    std::cin >> firstPerson >> secondPerson;

    std::vector<unsigned int> chemistryPoints;
    for (unsigned int nameIndex = 0; nameIndex < firstPerson.size(); ++nameIndex)
    {
        chemistryPoints.push_back(ALPHABET_STROKES[firstPerson[nameIndex] - 'A']);
        chemistryPoints.push_back(ALPHABET_STROKES[secondPerson[nameIndex] - 'A']);
    }

    while (chemistryPoints.size() > CHEMISTRY_POINT_COMPARE_COUNT)
    {
        std::vector<unsigned int> tempPoints;
        for (unsigned int i = 0; i < chemistryPoints.size() - 1; ++i)
        {
            tempPoints.push_back((chemistryPoints[i] + chemistryPoints[i + 1]) % 10);
        }

        chemistryPoints.swap(tempPoints);
    }

PRINT_LABEL:
    for (unsigned int point : chemistryPoints)
    {
        std::cout << point;
    }

    return 0;
}