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

messi(8): Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi
          Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi

messi(9): Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi
          Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi

messi(10):Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi
          Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi
          Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi Messi Gimossi Messi Messi Gimossi

*/

int GetScaledDownIndexOfShoutRecursive(int shoutSize, int prevShoutSize, int shoutIndex)
{
    if (shoutIndex < shoutSize)
    {
        return shoutIndex;
    }

    int scaledDownShoutIndex = GetScaledDownIndexOfShoutRecursive(shoutSize + prevShoutSize + 1, shoutSize, shoutIndex);
    if (scaledDownShoutIndex < shoutSize)
    {
        return scaledDownShoutIndex;
    }

    return scaledDownShoutIndex - shoutSize - 1;
}


int main()
{
    int shoutIndex = 0;
    std::cin >> shoutIndex;
    shoutIndex--;

    std::string previousShout = "Messi";
    std::string currentShout = "Messi Gimossi";

    int scaledDownShoutIndex = GetScaledDownIndexOfShoutRecursive(currentShout.size(), previousShout.size(), shoutIndex);

    if (scaledDownShoutIndex == -1 || scaledDownShoutIndex == 5)
    {
        std::cout << "Messi Messi Gimossi";
    }
    else
    {
        std::cout << currentShout[scaledDownShoutIndex];
    }

    return 0;
}