#include <cs50.h>
#include <stdio.h>

float    calculate(char c, int n, float *array)
{
    int i = 0;
    float result = 0;

    while (i < n)
        result += array[i++];
    if (c == 'T')
        return (result);
    return (result/n);
}

int main(void)
{
    int n = get_int("Number of weeks taking CS50: ");
    int i = 0;
    float array[n];

    while (i < n)
    {
        array[i] = get_int("Week %i HW Hours: ", i);
        i++;
    }
    char x = get_char("Enter T for total hours, A for average hours per week: ");
    printf("%.1f\n", calculate(x,n,array));
}