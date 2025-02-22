
#include <iostream>
#include <string>
#include <unordered_map>

/*

messi(1): Messi
messi(2)​​: Messi Gimossi
messi(3)​​​​​​: Messi Gimossi Messi
messi(4): Messi Gimossi Messi Messi Gimossi
messi(5): Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi
messi(6): Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi
messi(7): Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi
messi(8): Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi
messi(9): Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi
          Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi
*/

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
        nextShout += currentShout;
        nextShout += ' ';
        nextShout += previousShout;
        
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