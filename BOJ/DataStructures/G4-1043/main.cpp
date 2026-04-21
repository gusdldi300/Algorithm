#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

#define MAX_PEOPLE_COUNT (51U)
#define MAX_PARTIES_COUNT (51U)

int main()
{
    unsigned int peopleCount;
    unsigned int partiesCount;

    std::cin >> peopleCount >> partiesCount;


    unsigned int truthsCount;   
    std::cin >> truthsCount;

    std::vector<unsigned int> truthPeople;

    for (unsigned int i = 0; i < truthsCount; ++i)
    {
        unsigned int truthPerson;
        std::cin >> truthPerson;

        truthPeople.push_back(truthPerson);
    }

    std::unordered_set<unsigned int> partiesParticipantSet[MAX_PARTIES_COUNT];

    for (unsigned int i = 0; i < partiesCount; ++i)
    {
        unsigned int participantsCount;
        std::cin >> participantsCount;

        for (unsigned int j = 0; j < participantsCount; ++j)
        {
            unsigned int participant;
            std::cin >> participant;

            partiesParticipantSet[i].insert(participant);
        }
    }

    bool bTruthParties[MAX_PARTIES_COUNT] = { false, };
    
    bool bVisitedPeople[MAX_PEOPLE_COUNT] = { false, };
    std::queue<unsigned int> truthQueue;

    for (unsigned int i = 0; i < truthsCount; ++i)
    {
        truthQueue.push(truthPeople[i]);
        bVisitedPeople[truthPeople[i]] = true;

        while (truthQueue.empty() == false)
        {
            unsigned int truthPerson = truthQueue.front();
            truthQueue.pop();

            for (unsigned int partiesIndex = 0; partiesIndex < partiesCount; ++partiesIndex)
            {
                if (bTruthParties[partiesIndex])
                {
                    continue;
                }

                if (partiesParticipantSet[partiesIndex].find(truthPerson) == partiesParticipantSet[partiesIndex].end())
                {
                    continue;
                }

                for (unsigned int nextTruthPerson : partiesParticipantSet[partiesIndex])
                {
                    if (bVisitedPeople[nextTruthPerson])
                    {
                        continue;
                    }

                    truthQueue.push(nextTruthPerson);
                    bVisitedPeople[nextTruthPerson] = true;
                }

                bTruthParties[partiesIndex] = true;
            }
        }
    }

    unsigned int falsePartiesCount = 0;
    for (unsigned int partiesIndex = 0; partiesIndex < partiesCount; ++partiesIndex)
    {
        if (bTruthParties[partiesIndex] == false)
        {
            falsePartiesCount++;
        }
    }

    std::cout << falsePartiesCount;

    return 0; 
}