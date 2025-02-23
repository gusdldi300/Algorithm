#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
    unsigned int shoutIndex = 0;
    std::cin >> shoutIndex;
    --shoutIndex;

    std::string previousShout = "Messi";
    std::string currentShout = "Messi Gimossi";

    char foundCharacter;
    if (shoutIndex < previousShout.size())
    {
        foundCharacter = previousShout[shoutIndex];
        goto character_found;
    }

    if (shoutIndex < currentShout.size())
    {
        foundCharacter = currentShout[shoutIndex];
        goto character_found;
    }

    while (true)
    {
        std::string nextShout;
        nextShout.reserve(previousShout.size() + currentShout.size() + 1);
        nextShout += previousShout;
        nextShout += ' ';
        nextShout += currentShout;

        if (shoutIndex < nextShout.size())
        {
            foundCharacter = nextShout[shoutIndex];
            break;
        }

        previousShout.swap(currentShout);
        currentShout.swap(nextShout);
    }

character_found:

    if (foundCharacter == ' ')
    {
        std::cout << "Messi Messi Gimossi";
    }
    else
    {
        std::cout << foundCharacter;
    }

    return 0;
}