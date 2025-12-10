
#include <iostream>

#define MAX_DRUG_COUNT (31)

static long long sCases[MAX_DRUG_COUNT][MAX_DRUG_COUNT] = { 0, };

static long long EatDrugCasesRecursive(int wholeDrug, int halfDrug)
{
    if (halfDrug < 0)
    {
        return 0;
    }

    if (wholeDrug == 0)
    {
        return 1;
    }

    if (sCases[wholeDrug][halfDrug] > 0)
    {
        return sCases[wholeDrug][halfDrug];
    }

    long long eatCase = EatDrugCasesRecursive(wholeDrug, halfDrug - 1) + EatDrugCasesRecursive(wholeDrug - 1, halfDrug + 1);
    sCases[wholeDrug][halfDrug] = eatCase;

    return eatCase;
}

int main()
{
    while (true)
    {
        unsigned int wholeDrugCount;

        std::cin >> wholeDrugCount;

        if (wholeDrugCount == 0)
        {
            break;
        }

        std::cout << EatDrugCasesRecursive(wholeDrugCount, 0) << std::endl;
    }

    return 0;
}