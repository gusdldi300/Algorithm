#include <iostream>
#include <vector>
#include <unordered_set>

#define MAX_STUDENTS_COUNT (100001U)

static bool IsGroupedAndGetGroupCountRecursive(unsigned int student, unsigned int& lastStudent, bool bVisited[], std::unordered_set<unsigned int>& groupedStudents, unsigned int* outGroupCount, const std::vector<unsigned int>& preferredStudents)
{
    if (groupedStudents.find(student) != groupedStudents.end())
    {
        lastStudent = student;

        return true;
    }

    if (bVisited[student])
    {
        return false;
    }

    groupedStudents.insert(student);

    bool bGrouped = IsGroupedAndGetGroupCountRecursive(preferredStudents[student], lastStudent, bVisited, groupedStudents, outGroupCount, preferredStudents);

    bVisited[student] = true;
    groupedStudents.erase(student);

    if (bGrouped)
    {
        ++(*outGroupCount);

        if (student == lastStudent)
        {
            return false;
        }
    }

    return bGrouped;
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int testsCount;
    std::cin >> testsCount;

    for (unsigned int i = 0; i < testsCount; ++i)
    {
        unsigned int studentsCount;
        std::cin >> studentsCount;

        std::vector<unsigned int> preferredStudents;
        for (unsigned int j = 0; j < studentsCount; ++j)
        {
            unsigned int student;
            std::cin >> student;

            preferredStudents.push_back(student - 1);
        }

        unsigned int groupCount = 0;

        std::unordered_set<unsigned int> groupedStudents;
        bool bVisited[MAX_STUDENTS_COUNT] = { false, };
        unsigned int lastStudent = MAX_STUDENTS_COUNT;

        for (unsigned int student = 0; student < studentsCount; ++student)
        {
            IsGroupedAndGetGroupCountRecursive(student, lastStudent, bVisited, groupedStudents, &groupCount, preferredStudents);
        }

        std::cout << (studentsCount - groupCount) << '\n';
    }

    return 0;
}