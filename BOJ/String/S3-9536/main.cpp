
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

int main()
{
    unsigned int testsCount;
    std::cin >> testsCount;
    std::cin.ignore();

    for (unsigned int i = 0; i < testsCount; ++i)
    {
        std::vector<std::string> cryingSounds;

        std::string line;
        std::getline(std::cin, line);

        std::string cryingSound;
        for (unsigned int lineIndex = 0; lineIndex < line.size(); ++lineIndex)
        {
            if (line[lineIndex] == ' ')
            {
                cryingSounds.push_back(cryingSound);
                cryingSound.clear();

                continue;
            }

            cryingSound.push_back(line[lineIndex]);
        }

        cryingSounds.push_back(cryingSound);
        
        std::unordered_set<std::string> cryingSoundSet;
        while (true)
        {
            std::getline(std::cin, line);

            if (line[line.size() - 1] == '?')
            {
                break;
            }
            
            unsigned int spaceCount = 0;
            std::string animalSound;
            for (unsigned int lineIndex = 0; lineIndex < line.size(); ++lineIndex)
            {
                if (line[lineIndex] == ' ')
                {
                    spaceCount++;

                    continue;
                }

                if (spaceCount == 2)
                {
                    animalSound.push_back(line[lineIndex]);
                }
            }

            cryingSoundSet.insert(animalSound);
        }

        std::string wolfSounds;
        for (const std::string& sound : cryingSounds)
        {
            if (cryingSoundSet.find(sound) == cryingSoundSet.end())
            {
                wolfSounds.append(sound);
                wolfSounds.push_back(' ');
            }
        }

        std::cout << wolfSounds << std::endl;
    }

    return 0;
}