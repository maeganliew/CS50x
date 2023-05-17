#include <cs50.h>
#include <stdio.h>

void    pyramid(int n)
{
    if (n <= 0)
        return ;
    pyramid(n - 1);
    for (int i = 0; i < n; i++)
        printf("#");
    printf("\n");
}

int main(void)
{
    int n = get_int("Heights of blocks: ");
    pyramid(n);
    return 0;
}