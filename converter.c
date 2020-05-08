#include <stdio.h>
int main()
{
    int n, c, k;

    char str[] = "4";
    sscanf(str, "%d", &n);

    printf("%d in binary number system is:\n", n);

    for (c = 15; c >= 0; c--)
    {
        k = n >> c;

        if (k & 1)
            printf("1");
        else
            printf("0");
    }

    printf("\n");

    return 0;
}