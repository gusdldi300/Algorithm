
#include <cstring>
#include <iostream>
#include <list>
#include <vector>

#define MAX_STUDENTS_COUNT (32001U)

std::vector<unsigned int> sTallerStudentLists[MAX_STUDENTS_COUNT];
bool sbVisited[MAX_STUDENTS_COUNT] = { false, };

static void SortStudentHeightsRecursive(unsigned int student, std::list<unsigned int>* outStudentHeightsAscend)
{
    for (unsigned int nextStudent : sTallerStudentLists[student])
    {
        if (sbVisited[nextStudent])
        {
            continue;
        }
        
        sbVisited[nextStudent] = true;
        SortStudentHeightsRecursive(nextStudent, outStudentHeightsAscend);
    }

    outStudentHeightsAscend->push_front(student);
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int studentsCount;
    unsigned int compareCount;
    
    std::cin >> studentsCount >> compareCount;
    for (unsigned int i = 0; i < compareCount; ++i)
    {
        unsigned int student;
        unsigned int tallerStudent;

        std::cin >> student >> tallerStudent;
        sTallerStudentLists[student].push_back(tallerStudent);

        sbVisited[tallerStudent] = true;
    }

    std::vector<unsigned int> startStudents;
    for (unsigned int student = 1; student <= studentsCount; ++student)
    {
        if (sbVisited[student] == false)
        {
            startStudents.push_back(student);
        }
    }

    memset(sbVisited, false, sizeof(sbVisited));

    std::list<unsigned int> studentHeightsAscend;
    for (unsigned int startStudent : startStudents)
    {
        sbVisited[startStudent] = true;

        SortStudentHeightsRecursive(startStudent, &studentHeightsAscend);
    }

    for (unsigned int student : studentHeightsAscend)
    {
        std::cout << student << " ";
    }

    return 0;
}

