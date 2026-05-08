#include <iostream>
#include <vector>
#include <queue>

#define MAX_PROBLEMS_COUNT (32001U)

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int problemsCount;
    unsigned int informationsCount;
    std::cin >> problemsCount >> informationsCount;

    std::vector<unsigned int> nextProblemLists[MAX_PROBLEMS_COUNT];
    unsigned int lastProblemCounts[MAX_PROBLEMS_COUNT] = { 0, };

    for (unsigned int i = 0; i < informationsCount; ++i)
    {
        unsigned int problem;
        unsigned int nextProblem;

        std::cin >> problem >> nextProblem;

        nextProblemLists[problem].push_back(nextProblem);
        ++lastProblemCounts[nextProblem];
    }

    std::priority_queue<unsigned int, std::vector<unsigned int>, std::greater<unsigned int>> problemQueueAscend;
    for (unsigned int problem = 1; problem <= problemsCount; ++problem)
    {
        if (lastProblemCounts[problem] == 0)
        {
            problemQueueAscend.push(problem);
        }
    }

    while (problemQueueAscend.empty() == false)
    {
        unsigned int problem = problemQueueAscend.top();
        problemQueueAscend.pop();

        std::cout << problem << ' ';

        for (unsigned int nextProblem : nextProblemLists[problem])
        {
            --lastProblemCounts[nextProblem];
            
            if (lastProblemCounts[nextProblem] == 0)
            {
                problemQueueAscend.push(nextProblem);
            }
        }
    }

    return 0;
}