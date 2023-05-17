#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = get_int("Height: \n");

    for (int n = 0; n < height; n++)
    {
        int i = 1;
        int j = 1;
        while(i + n < height)
        {
            printf(" ");
            i++;
        }
        while(j + n > 0)
        {
            printf("#");
            j--;
        }
        printf("\n");
    }
    return 0;
}