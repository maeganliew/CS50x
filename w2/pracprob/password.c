#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    int i = 0;
    int a, b, c, d;
    string pass = get_string("Enter your password: ");
    while (pass[i])
    {
        if (isupper(pass[i]))
            a = 1;
        if (islower(pass[i]))
            b = 1;
        if (isdigit(pass[i]))
            c = 1;
        if (pass[i] == '(' || pass[i] == ')' || pass[i] =='!')
            d = 1;
        i++;
    }
    if (a + b + c + d == 4)
        printf("Your password is valid!\n");
    else
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol!\n");
}