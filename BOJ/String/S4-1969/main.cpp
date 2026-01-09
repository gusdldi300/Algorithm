
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

#define MAX_NUCLEOTIDES_COUNT (4U)

static const char NUCLEOTIDES[MAX_NUCLEOTIDES_COUNT] = { 'A', 'C', 'G', 'T' };

static unsigned int sDnasCount;
static unsigned int sDnaLength;

static unsigned int GetHammingDistance(const std::string& dna, const std::vector<std::string>& compareDnas)
{
    unsigned int hammingDistance = 0;

    for (unsigned int i = 0; i < compareDnas.size(); ++i)
    {
        const std::string& compareDna = compareDnas[i];

        for (unsigned int j = 0; j < compareDna.length(); ++j)
        {
            if (dna[j] != compareDna[j])
            {
                hammingDistance++;
            }
        }
    }

    return hammingDistance;
}

static void GetMinHammingDistanceDnaRecursive(std::string& dna, const std::vector<std::string>& compareDnas, std::string* outMinDistanceDna, unsigned int* outMinHammingDistance)
{
    if (dna.length() == sDnaLength)
    {
        unsigned int hammingDistance = GetHammingDistance(dna, compareDnas);
        if (hammingDistance < *outMinHammingDistance)
        {
            *outMinDistanceDna = dna;
            *outMinHammingDistance = hammingDistance;
        }

        return;
    }

    for (unsigned int i = 0; i < MAX_NUCLEOTIDES_COUNT; ++i)
    {
        char addNucleotide = NUCLEOTIDES[i];

        dna.push_back(addNucleotide);
        GetMinHammingDistanceDnaRecursive(dna, compareDnas, outMinDistanceDna, outMinHammingDistance);

        dna.pop_back();
    }
}

int main()
{
    
    std::cin >> sDnasCount >> sDnaLength;

    std::vector<std::string> compareDnas;
    for (unsigned int i = 0; i < sDnasCount; ++i)
    {
        std::string dna;
        dna.reserve(sDnaLength);

        std::cin >> dna;

        compareDnas.push_back(dna);
    }

    unsigned int minHammingDistance = UINT_MAX;
    std::string minDistanceDna;

    std::string dna;
    dna.reserve(sDnaLength);

    GetMinHammingDistanceDnaRecursive(dna, compareDnas, &minDistanceDna, &minHammingDistance);

    std::cout << minDistanceDna << std::endl << minHammingDistance << std::endl;

    return 0;
}