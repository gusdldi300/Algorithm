
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Problem
{
    unsigned int DeadLine;
    unsigned int Price;
};

struct PriorityQueueComparator
{
    bool operator()(const Problem& first, const Problem& second) 
    {
        return first.Price > second.Price;
    }
};

static bool CompareProblemsForSort(const Problem& first, const Problem& second)
{
    if (first.DeadLine == second.DeadLine)
    {
        return first.Price > second.Price;
    }

    return first.DeadLine < second.DeadLine;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int problemsCount;
    std::cin >> problemsCount;

    std::vector<Problem> problemsDeadLineAscend;
    for (unsigned int i = 0; i < problemsCount; ++i)
    {
        Problem problem;
        std::cin >> problem.DeadLine >> problem.Price;

        problemsDeadLineAscend.push_back(problem);
    }
    
    std::sort(problemsDeadLineAscend.begin(), problemsDeadLineAscend.end(), CompareProblemsForSort);
    
    std::priority_queue<Problem, std::vector<Problem>, PriorityQueueComparator> problemMinPriceQueue;
    for (const Problem& problem : problemsDeadLineAscend)
    {
        if (problem.DeadLine <= problemMinPriceQueue.size())
        {
            if (problem.Price <= problemMinPriceQueue.top().Price)
            {
                continue;
            }

            problemMinPriceQueue.pop();
        }

        problemMinPriceQueue.push(problem);
    }

    unsigned int totalPrice = 0;
    while (problemMinPriceQueue.empty() == false)
    {
        totalPrice += problemMinPriceQueue.top().Price;
        
        problemMinPriceQueue.pop();
    }

    std::cout << totalPrice;

    return 0;
}