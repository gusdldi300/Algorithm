#include <iostream>
#include <map>
#include <set>
#include <unordered_map>

class Problem
{
public:
    bool operator<(const Problem& other) const
    {
        if (this->Difficulty == other.Difficulty)
        {
            return this->Number < other.Number;
        }

        return this->Difficulty < other.Difficulty;
    }

    int Number;
    int Difficulty;
};

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int problemsCount;
    std::cin >> problemsCount;

    std::unordered_map<unsigned int, unsigned int> problemDifficultyMap;
    std::set<Problem> problemSetAscend;
    for (unsigned int i = 0; i < problemsCount; ++i)
    {
        Problem problem;
        std::cin >> problem.Number >> problem.Difficulty;

        problemSetAscend.insert(problem);
        problemDifficultyMap[problem.Number] = problem.Difficulty;
    }

    unsigned int queriesCount;
    std::cin >> queriesCount;
    for (unsigned int i = 0; i < queriesCount; ++i)
    {
        std::string query;
        std::cin >> query;
        
        if (query == "add")
        {
            Problem newProblem;
            std::cin >> newProblem.Number >> newProblem.Difficulty;

            problemSetAscend.insert(newProblem);
            problemDifficultyMap[newProblem.Number] = newProblem.Difficulty;
        }
        else if (query == "solved")
        {
            unsigned int problemNumber;
            std::cin >> problemNumber;

            Problem deleteProblem;
            deleteProblem.Number = problemNumber;
            deleteProblem.Difficulty = problemDifficultyMap[problemNumber];

            problemSetAscend.erase(deleteProblem);
            problemDifficultyMap.erase(problemNumber);
        }
        else
        {
            int recommendDifficulty;
            std::cin >> recommendDifficulty;
            
            unsigned int recommendProblem;
            if (recommendDifficulty == 1)
            {
                recommendProblem = problemSetAscend.rbegin()->Number;
            }
            else
            {
                recommendProblem = problemSetAscend.begin()->Number;
            }

            std::cout << recommendProblem << '\n';
        }
    }

    return 0;
}