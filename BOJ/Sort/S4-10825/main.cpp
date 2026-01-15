#include <iostream>
#include <vector>
#include <algorithm>

struct Student
{
    std::string Name;
    unsigned int KoreanScore;
    unsigned int EnglishScore;
    unsigned int MathScore;
};

static bool CompareStudent(const Student& first, const Student& second)
{
    if (first.KoreanScore == second.KoreanScore)
    {
        if (first.EnglishScore == second.EnglishScore)
        {
            if (first.MathScore == second.MathScore)
            {
                return first.Name < second.Name;
            }
            
            return first.MathScore > second.MathScore;
        }

        return first.EnglishScore < second.EnglishScore;
    }

    return first.KoreanScore > second.KoreanScore;
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int studentsCount;
    std::cin >> studentsCount;

    std::vector<Student> studentsOrdered;
    for (unsigned int i = 0; i < studentsCount; ++i)
    {
        Student student;
        std::cin >> student.Name >> student.KoreanScore >> student.EnglishScore >> student.MathScore;

        studentsOrdered.push_back(student);
    }

    std::sort(studentsOrdered.begin(), studentsOrdered.end(), CompareStudent);
    for (const Student& student : studentsOrdered)
    {
        std::cout << student.Name << '\n';
    }

    return 0;
}