#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int *x;
    int *y;

    x = malloc(sizeof(int));
    *x = 20;

    // *y = 13; is wrong cuz y not malloced
    y = x;
    *y = 13;
    printf("%i", *y);
}