
#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
#include <queue>

#define MAX_CLASSES_COUNT (1001U)

class Student
{
public:
    bool operator<(const Student& other) const
    {
        return Ability > other.Ability;
    }

public:
    unsigned int Class;
    unsigned int Index;
    unsigned int Ability;
};

int main()
{
    unsigned int classesCount;
    unsigned int studentsCount;

    std::cin >> classesCount >> studentsCount;

    std::vector<unsigned int> classesAscend[MAX_CLASSES_COUNT];

    for (unsigned int classIndex = 0; classIndex < classesCount; ++classIndex)
    {
        for (unsigned int i = 0; i < studentsCount; ++i)
        {
            unsigned int ability;
            std::cin >> ability;

            classesAscend[classIndex].push_back(ability);
        }
    }

    for (unsigned int classIndex = 0; classIndex < classesCount; ++classIndex)
    {
        std::sort(classesAscend[classIndex].begin(), classesAscend[classIndex].end());
    }

    unsigned int maxAbility = 0;

    std::priority_queue<Student> abilitiesAscend;
    for (unsigned int classIndex = 0; classIndex < classesCount; ++classIndex)
    {
        Student student;
        student.Class = classIndex;
        student.Index = 0;
        student.Ability = classesAscend[classIndex][0];

        maxAbility = std::max(maxAbility, student.Ability);

        abilitiesAscend.push(std::move(student));
    }

    unsigned int minAbilityDiff = UINT_MAX;
    while (true)
    {
        Student minAbilityStudent = abilitiesAscend.top();
        abilitiesAscend.pop();

        minAbilityDiff = std::min(minAbilityDiff, maxAbility - minAbilityStudent.Ability);

        if (minAbilityStudent.Index >= (studentsCount - 1))
        {
            break;
        }

        Student newStudent;
        newStudent.Class = minAbilityStudent.Class;
        newStudent.Index = minAbilityStudent.Index + 1;
        newStudent.Ability = classesAscend[newStudent.Class][newStudent.Index];

        maxAbility = std::max(maxAbility, newStudent.Ability);

        abilitiesAscend.push(std::move(newStudent));
    }

    std::cout << minAbilityDiff;

    return 0;
}