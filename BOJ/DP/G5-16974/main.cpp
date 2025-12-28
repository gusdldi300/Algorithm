
#include <string>
#include <iostream>

#define MAX_LEVEL (51U)

struct IngredientCount
{
    long long Total;
    long long Patty;
};

static long long sPattyCounts[MAX_LEVEL] = { 0, };
static long long sIngredientCounts[MAX_LEVEL] = { 0, };

static IngredientCount GetIngredientPattyCountRecursive(unsigned int level)
{
    if (sIngredientCounts[level] > 0)
    {
        return { sIngredientCounts[level], sPattyCounts[level] };
    }

    IngredientCount ingredientCount = { 3, 1 };

    IngredientCount tempCount = GetIngredientPattyCountRecursive(level - 1);
    ingredientCount.Total += tempCount.Total;
    ingredientCount.Patty += tempCount.Patty;

    tempCount = GetIngredientPattyCountRecursive(level - 1);
    ingredientCount.Total += tempCount.Total;
    ingredientCount.Patty += tempCount.Patty;

    sIngredientCounts[level] = ingredientCount.Total;
    sPattyCounts[level] = ingredientCount.Patty;

    return ingredientCount;
}

static long long GetPattyAteCountRecursive(unsigned int level, long long ateCount, long long* outAtePattyCount)
{
    if (ateCount <= 0)
    {
        return 0;
    }
    
    if (ateCount >= sIngredientCounts[level])
    {
        (*outAtePattyCount) += sPattyCounts[level];
        return ateCount - sIngredientCounts[level];
    }

    long long newAteCount = ateCount;
    --newAteCount;

    newAteCount = GetPattyAteCountRecursive(level - 1, newAteCount, outAtePattyCount);
    if (newAteCount > 0)
    {
        --newAteCount;
        (*outAtePattyCount)++;

        newAteCount = GetPattyAteCountRecursive(level - 1, newAteCount, outAtePattyCount);
        --newAteCount;
    }
    
    return newAteCount;
}


int main()
{
    unsigned int targetLevel;
    long long ateCount; 
    
    std::cin >> targetLevel;
    std::cin >> ateCount;

    sIngredientCounts[0] = 1;
    sPattyCounts[0] = 1;

    GetIngredientPattyCountRecursive(targetLevel);

    long long pattyAteCount = 0;
    GetPattyAteCountRecursive(targetLevel, ateCount, &pattyAteCount);

    std::cout << pattyAteCount;

    return 0;
}