#include <stdio.h>

int main(void)
{
    /*char *c = "hello";
    for (int    i = 0; i < 6; i++)
    {
        printf("%p\n", &c[i]);
    }*/

    int n = 5;
    int *p = &n;
    printf("%i", *p);
}