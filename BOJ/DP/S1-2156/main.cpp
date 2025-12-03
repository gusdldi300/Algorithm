
#include <iostream>

#define MAX_WINE_GLASS_COUNT (10000U)
#define MAX_CONTINUOS_DRINK_COUNT (3U)

static unsigned int sWineGlasses[MAX_WINE_GLASS_COUNT];
static unsigned int sDrinkAmounts[MAX_WINE_GLASS_COUNT][MAX_CONTINUOS_DRINK_COUNT] = { 0, };

int main()
{
    unsigned int glassCount = 0;
    std::cin >> glassCount;

    for (unsigned int glass = 0; glass < glassCount; ++glass)
    {
        std::cin >> sWineGlasses[glass];
    }

    unsigned int maxAmount = 0;
    if (glassCount == 1)
    {
        maxAmount = sWineGlasses[0];
        goto COMPLETE_LABEL;
    }

    sDrinkAmounts[0][1] = sWineGlasses[0];
    sDrinkAmounts[0][2] = sWineGlasses[0];

    sDrinkAmounts[1][0] = sWineGlasses[0];
    sDrinkAmounts[1][1] = sWineGlasses[1];
    sDrinkAmounts[1][2] = sDrinkAmounts[0][1] + sWineGlasses[1];

    for (unsigned int glass = 2; glass < glassCount; ++glass)
    {
        unsigned int lastGlass = glass - 1;

        sDrinkAmounts[glass][0] = std::max(sDrinkAmounts[lastGlass][0], sDrinkAmounts[lastGlass][1]);
        sDrinkAmounts[glass][0] = std::max(sDrinkAmounts[glass][0], sDrinkAmounts[lastGlass][2]);

        sDrinkAmounts[glass][1] = sWineGlasses[glass] + sDrinkAmounts[lastGlass][0];
        sDrinkAmounts[glass][2] = sWineGlasses[glass] + sDrinkAmounts[lastGlass][1];
    }

    maxAmount = std::max(sDrinkAmounts[glassCount - 1][0], sDrinkAmounts[glassCount - 1][1]);
    maxAmount = std::max(maxAmount, sDrinkAmounts[glassCount - 1][2]);

COMPLETE_LABEL:
    std::cout << maxAmount;

    return 0;
}