
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_PAPERS_COUNT (101U)

struct Paper
{
    unsigned int LongLength;
    unsigned int ShortLength;
};

static bool ComparePapers(const Paper& first, const Paper& second)
{
    if (first.LongLength == second.LongLength)
    {
        return first.ShortLength < second.ShortLength;
    }

    return first.LongLength < second.LongLength;
}

int main()
{
    unsigned int papersCount;
    std::cin >> papersCount;

    std::vector<Paper> longLengthAscendPapers;
    for (unsigned int i = 0; i < papersCount; ++i)
    {
        Paper paper;
        std::cin >> paper.LongLength >> paper.ShortLength;

        if (paper.LongLength < paper.ShortLength)
        {
            unsigned int tempLength = paper.LongLength;
            paper.LongLength = paper.ShortLength;
            paper.ShortLength = tempLength;
        }

        longLengthAscendPapers.push_back(std::move(paper));
    }

    std::sort(longLengthAscendPapers.begin(), longLengthAscendPapers.end(), ComparePapers);
    
    unsigned int maxOverlappedPaperCounts[MAX_PAPERS_COUNT] = { 0, };
    maxOverlappedPaperCounts[0] = 1;
    for (unsigned int i = 1; i < longLengthAscendPapers.size(); ++i)
    {
        const Paper& paper = longLengthAscendPapers[i];

        for (unsigned int j = 0; j < i; j++)
        {
            if (paper.ShortLength >= longLengthAscendPapers[j].ShortLength)
            {
                maxOverlappedPaperCounts[i] = std::max(maxOverlappedPaperCounts[i], maxOverlappedPaperCounts[j]);
            }
        }

        maxOverlappedPaperCounts[i]++;
    }

    unsigned int maxOverlappedCount = 0;
    for (unsigned int i = 0; i < longLengthAscendPapers.size(); ++i)
    {
        maxOverlappedCount = std::max(maxOverlappedCount, maxOverlappedPaperCounts[i]);
    }

    std::cout << maxOverlappedCount;

    return 0;
}