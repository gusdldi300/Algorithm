
#include <iostream>
#include <cstdio>

#define MAX_RETURN_VALUE (20)
#define MAX_PARAMETER_VALUE (51U)

static int sReturnValues[MAX_PARAMETER_VALUE][MAX_PARAMETER_VALUE][MAX_PARAMETER_VALUE] = { 0, };

int wRecursive(int a, int b, int c) 
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        return 1;
    }

    if (sReturnValues[a][b][c] > 0)
    {
        return sReturnValues[a][b][c];
    }

    int result = 0;
    if (a > MAX_RETURN_VALUE || b > MAX_RETURN_VALUE || c > MAX_RETURN_VALUE)
    {
        result = wRecursive(MAX_RETURN_VALUE, MAX_RETURN_VALUE, MAX_RETURN_VALUE);
    }
    else if (a < b && b < c)
    {
        result = wRecursive(a, b, c - 1) + wRecursive(a, b - 1, c - 1) - wRecursive(a, b - 1, c);
    }
    else
    {
        result = wRecursive(a - 1, b, c) + wRecursive(a - 1, b - 1, c)
            + wRecursive(a - 1, b, c - 1) - wRecursive(a - 1, b - 1, c - 1);
    }

    sReturnValues[a][b][c] = result;

    return result;
}

int main()
{
    int a = 0;
    int b = 0;
    int c = 0;

    while (true)
    {
        std::cin >> a >> b >> c;
        if (a == -1 && b == -1 && c == -1)
        {
            break;
        }

        printf("w(%d, %d, %d) = %d\n", a, b, c, wRecursive(a, b, c));
    }

    return 0;
}