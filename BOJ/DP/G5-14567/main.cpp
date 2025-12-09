
#include <iostream>
#include <string>

#define MAX_COURSES_COUNT (1001)

static bool sbNextCourses[MAX_COURSES_COUNT][MAX_COURSES_COUNT] = { false, };
static unsigned int sCompleteSemesters[MAX_COURSES_COUNT];

static void SetCompleteSemesterRecursive(unsigned int course, unsigned int semester, const unsigned int maxCourses)
{
    unsigned int completeSemester = semester;
    if (completeSemester < sCompleteSemesters[course])
    {
        completeSemester = sCompleteSemesters[course];
    }
    
    sCompleteSemesters[course] = completeSemester;

    for (unsigned int nextCourse = course + 1; nextCourse <= maxCourses; ++nextCourse)
    {
        if (sbNextCourses[course][nextCourse] == false)
        {
            continue;
        }

        SetCompleteSemesterRecursive(nextCourse, completeSemester + 1, maxCourses);
    }
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

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

        sbNextCourses[prerequisite][course] = true;
    }

    for (unsigned int course = 1; course <= coursesCount; ++course)
    {
        SetCompleteSemesterRecursive(course, 1, coursesCount);
    }

    std::string printSemesters;
    for (unsigned int course = 1; course <= coursesCount; ++course)
    {
        printSemesters.append(std::to_string(sCompleteSemesters[course]));
        printSemesters.append(" ");
    }

    std::cout << printSemesters;

    return 0;
}