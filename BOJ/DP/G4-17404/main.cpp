
#include <iostream>
#include <climits>

#define MAX_COLORS_COUNT (3U)
#define MAX_HOUSES_COUNT (1001U)

static unsigned int sHouseColorPrices[MAX_HOUSES_COUNT][MAX_COLORS_COUNT];
static unsigned int sMinPrices[MAX_HOUSES_COUNT][MAX_COLORS_COUNT];

int main()
{
    unsigned int housesCount;
    std::cin >> housesCount;

    for (unsigned int housesIndex = 0; housesIndex < housesCount; ++housesIndex)
    {
        for (unsigned int colorsIndex = 0; colorsIndex < MAX_COLORS_COUNT; ++colorsIndex)
        {
            unsigned int color;
            std::cin >> color;

            sHouseColorPrices[housesIndex][colorsIndex] = color;
        }
    }

    unsigned int minPrice = UINT_MAX;

    for (unsigned int startColor = 0; startColor < MAX_COLORS_COUNT; ++startColor)
    {
        for (unsigned int housesIndex = 0; housesIndex < housesCount; ++housesIndex)
        {
            for (unsigned int colorsIndex = 0; colorsIndex < MAX_COLORS_COUNT; ++colorsIndex)
            {
                sMinPrices[housesIndex][colorsIndex] = UINT_MAX;
            }
        }

        sMinPrices[0][startColor] = sHouseColorPrices[0][startColor];

        for (unsigned int housesIndex = 0; housesIndex < (housesCount - 1); ++housesIndex)
        {
            for (unsigned int colorsIndex = 0; colorsIndex < MAX_COLORS_COUNT; ++colorsIndex)
            {
                if (sMinPrices[housesIndex][colorsIndex] == UINT_MAX)
                {
                    continue;
                }

                for (unsigned int nextColorsIndex = 0; nextColorsIndex < MAX_COLORS_COUNT; ++nextColorsIndex)
                {
                    if (colorsIndex == nextColorsIndex)
                    {
                        continue;
                    }

                    sMinPrices[housesIndex + 1][nextColorsIndex] = std::min(sMinPrices[housesIndex + 1][nextColorsIndex],
                                                                            sMinPrices[housesIndex][colorsIndex] + sHouseColorPrices[housesIndex + 1][nextColorsIndex]);
                }
            }
        }

        for (unsigned int colorsIndex = 0; colorsIndex < MAX_COLORS_COUNT; ++colorsIndex)
        {
            if (startColor == colorsIndex)
            {
                continue;
            }

            minPrice = std::min(minPrice, sMinPrices[housesCount - 1][colorsIndex]);
        }
    }

    std::cout << minPrice;

    return 0;
}