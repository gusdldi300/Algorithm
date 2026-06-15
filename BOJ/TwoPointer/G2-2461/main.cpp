
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
        if (Ability == other.Ability)
        {
            return Index > other.Index;
        }

        return Ability > other.Ability;
    }

public:
    unsigned int ClassIndex;
    unsigned int Index;

    unsigned int Ability;
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int classesCount;
    unsigned int studentsCount;
    std::cin >> classesCount >> studentsCount;

    std::vector<unsigned int> studentsAscendClasses[MAX_CLASSES_COUNT];
    std::priority_queue<Student> studentsAscendQueue;

    unsigned int maxAbility = 0;
    for (unsigned int classIndex = 0; classIndex < classesCount; ++classIndex)
    {
        for (unsigned int i = 0; i < studentsCount; ++i)
        {
            unsigned int ability;
            std::cin >> ability;

            studentsAscendClasses[classIndex].push_back(ability);
        }

        std::sort(studentsAscendClasses[classIndex].begin(), studentsAscendClasses[classIndex].end());
        
        Student firstStudent;
        firstStudent.ClassIndex = classIndex;
        firstStudent.Index = 0;
        firstStudent.Ability = studentsAscendClasses[classIndex][0];

        studentsAscendQueue.push(firstStudent);

        maxAbility = std::max(maxAbility, firstStudent.Ability);
    }
    
    unsigned int minAbilityDiff = maxAbility - studentsAscendQueue.top().Ability;

    while (true)
    {
        Student minStudent = studentsAscendQueue.top();
        studentsAscendQueue.pop();

        if (minStudent.Index == (studentsCount - 1))
        {
            break;
        }

        Student newStudent;
        newStudent.ClassIndex = minStudent.ClassIndex;
        newStudent.Index = minStudent.Index + 1;
        newStudent.Ability = studentsAscendClasses[newStudent.ClassIndex][newStudent.Index];

        studentsAscendQueue.push(newStudent);

        maxAbility = std::max(maxAbility, newStudent.Ability);
        minAbilityDiff = std::min(minAbilityDiff, maxAbility - studentsAscendQueue.top().Ability);
    }

    std::cout << minAbilityDiff;

    return 0;
}