
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

#define MAX_NUCLEOTIDES_COUNT (4U)

static const char NUCLEOTIDES[MAX_NUCLEOTIDES_COUNT] = { 'A', 'C', 'G', 'T' };

static unsigned int sDnasCount;
static unsigned int sDnaLength;

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

    std::string minDistanceDna;
    unsigned int minHammingDistance = 0;

    for (unsigned int dnaIndex = 0; dnaIndex < sDnaLength; ++dnaIndex)
    {
        char minNucleotide;
        unsigned int minNucleotideDifference = UINT_MAX;

        for (unsigned int nucleotidesIndex = 0; nucleotidesIndex < MAX_NUCLEOTIDES_COUNT; ++nucleotidesIndex)
        {
            char nucleotide = NUCLEOTIDES[nucleotidesIndex];
            unsigned int nucleotideDifference = 0;

            for (const std::string& compareDna : compareDnas)
            {
                if (nucleotide != compareDna[dnaIndex])
                {
                    nucleotideDifference++;
                }
            }

            if (nucleotideDifference < minNucleotideDifference)
            {
                minNucleotide = nucleotide;
                minNucleotideDifference = nucleotideDifference;
            }
        }

        minDistanceDna.push_back(minNucleotide);
        minHammingDistance += minNucleotideDifference;
    }

    std::cout << minDistanceDna << std::endl << minHammingDistance << std::endl;

    return 0;
}