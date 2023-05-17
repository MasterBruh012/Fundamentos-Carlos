#include <stdio.h>
#include <stdlib.h>

int main()
{

    int n[10];

    for (int i = 0; i < 10; i++)
    {
        n[i] = i + 1;
        printf("%d \n", n[i]);
    }

    return 0;
}