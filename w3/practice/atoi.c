#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }
    printf("%i\n", convert(input));
}

int num = 0;

int convert(string input)
{
    int n = strlen(input);

    if (n == 0)
        return (0);
    for (int i = n - 1; i >= 0; i--)
    {
        int temp = input[i] - '0';
        input[i] = '\0';
        convert(input);
        num = num * 10 + temp;
        return (num);
    }
    return (num);
}