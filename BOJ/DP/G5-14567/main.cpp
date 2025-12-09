
#include <iostream>
#include <vector>
#include <string>

#define MAX_COURSES_COUNT (1001)

static std::vector<unsigned int> sPrerequisites[MAX_COURSES_COUNT];
static unsigned int sCompleteSemesters[MAX_COURSES_COUNT];

int main()
{
    unsigned int coursesCount;
    std::cin >> coursesCount;

    unsigned int prerequisitesCount;
    std::cin >> prerequisitesCount;

    for (unsigned int i = 0; i < prerequisitesCount; ++i)
    {
        unsigned int prerequisite;
        std::cin >> prerequisite;

        unsigned int course;
        std::cin >> course;

        sPrerequisites[course].push_back(prerequisite);
    }

    std::string printSemesters;
    for (unsigned int course = 1; course <= coursesCount; ++course)
    {
        for (unsigned int prerequisite : sPrerequisites[course])
        {
            sCompleteSemesters[course] = std::max(sCompleteSemesters[course], sCompleteSemesters[prerequisite]);
        }

        sCompleteSemesters[course]++;

        printSemesters.append(std::to_string(sCompleteSemesters[course]));
        printSemesters.append(" ");
    }

    std::cout << printSemesters;

    return 0;
}