#include <stdio.h>
#include <stdlib.h>

int main()
{

    int n[3][3];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            n[i][j] = j + 1;
            printf(" %d ", n[i][j]);
        }
        printf("\n");
    }

    return 0;
}