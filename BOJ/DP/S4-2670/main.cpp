
#include <cstdio>
#include <iostream>

#define MAX_FLOAT_COUNT (10000U)
#define FLOAT_ROUND_ADD_OFFSET (0.0005)

int main()
{
    double floats[MAX_FLOAT_COUNT] = { 0.f, };

    unsigned int floatCount = 0;
    std::cin >> floatCount;

    std::cin >> floats[0];

    double maxMultipleFloat = floats[0];
    double lastFloat = floats[0];
    for (unsigned int i = 1; i < floatCount; ++i)
    {
        std::cin >> floats[i];

        double compareFloat = lastFloat * floats[i];
        lastFloat = (compareFloat >= floats[i] ? compareFloat : floats[i]);

        maxMultipleFloat = (lastFloat > maxMultipleFloat ? lastFloat : maxMultipleFloat);
    }

    printf("%.3f", (maxMultipleFloat));

    return 0;
}