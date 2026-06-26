
#include <iostream>
#include <cassert>
#include <set>
#include <unordered_map>

#define MAX_PROBLEM_NUMBER (100001U)
#define MAX_CATEGORIES_COUNT (101U)

struct Problem
{
public:
    bool operator<(const Problem& other) const
    {
        if (Difficulty == other.Difficulty)
        {
            return Number < other.Number;
        }

        return Difficulty < other.Difficulty;
    }

    unsigned int Category;
    unsigned int Number;
    unsigned int Difficulty;
};

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int problemsCount;
    std::cin >> problemsCount;

    std::unordered_map<unsigned int, Problem> numberAndProblemMap;
    std::set<Problem> categorizedProblemsDiffcultyAscend[MAX_CATEGORIES_COUNT];
    std::set<Problem> problemsDiffcultyAscend;

    for (unsigned int i = 0; i < problemsCount; ++i)
    {
        Problem problem;

        std::cin >> problem.Number >> problem.Difficulty >> problem.Category;

        numberAndProblemMap.insert(std::make_pair(problem.Number, problem));
        categorizedProblemsDiffcultyAscend[problem.Category].insert(problem);
        problemsDiffcultyAscend.insert(problem);
    }

    unsigned int commandsCount;
    std::cin >> commandsCount;

    for (unsigned int i = 0; i < commandsCount; ++i)
    {
        std::string command;
        std::cin >> command;

        if (command == "recommend")
        {
            assert(problemsDiffcultyAscend.empty() == false);

            unsigned int category;
            int option;
            std::cin >> category >> option;

            unsigned int printNumber;
            if (option == 1)
            {
                printNumber = categorizedProblemsDiffcultyAscend[category].rbegin()->Number;
            }
            else
            {
                printNumber = categorizedProblemsDiffcultyAscend[category].begin()->Number;
            }

            std::cout << printNumber << '\n';
        }
        else if (command == "recommend2")
        {
            assert(problemsDiffcultyAscend.empty() == false);

            int option;
            std::cin >> option;

            Problem problem = { 0, };
            if (option == 1)
            {
                problem = *problemsDiffcultyAscend.rbegin();
            }
            else
            {
                problem = *problemsDiffcultyAscend.begin();
            }

            std::cout << problem.Number << '\n';
        }
        else if (command == "recommend3")
        {
            assert(problemsDiffcultyAscend.empty() == false);

            int option;
            std::cin >> option;

            unsigned int difficulty;
            std::cin >> difficulty;

            Problem difficultySearchProblem = { 0, 0, difficulty };
            if (option == 1)
            {
                auto lowerEqualIter = problemsDiffcultyAscend.lower_bound(difficultySearchProblem);
                if (difficulty > problemsDiffcultyAscend.rbegin()->Difficulty)
                {
                    std::cout << -1 << '\n';
                }
                else
                {
                    std::cout << lowerEqualIter->Number << '\n';
                }
            }
            else
            {
                if (difficulty <= problemsDiffcultyAscend.begin()->Difficulty)
                {
                    std::cout << -1 << '\n';
                }
                else
                {
                    auto upperIter = problemsDiffcultyAscend.upper_bound(difficultySearchProblem);
                    --upperIter;

                    std::cout << upperIter->Number << '\n';
                }
            }
        }
        else if (command == "add")
        {
            Problem newProblem;
            std::cin >> newProblem.Number >> newProblem.Difficulty >> newProblem.Category;
            
            numberAndProblemMap[newProblem.Number] = newProblem;
            categorizedProblemsDiffcultyAscend[newProblem.Category].insert(newProblem);
            problemsDiffcultyAscend.insert(newProblem);
        }
        else if (command == "solved")
        {
            assert(problemsDiffcultyAscend.empty() == false);

            unsigned int solvedProblemNumber;
            std::cin >> solvedProblemNumber;

            Problem solvedProblem = numberAndProblemMap[solvedProblemNumber];
            categorizedProblemsDiffcultyAscend[solvedProblem.Category].erase(solvedProblem);

            problemsDiffcultyAscend.erase(solvedProblem);
            numberAndProblemMap.erase(solvedProblemNumber);
        }
        else
        {
            assert(false);
        }
    }

    return 0;
}