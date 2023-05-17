// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

string replace(char *d)
{
    int i = 0;
    char *c = d;
    while(c[i] != '\0')
    {
        if (c[i] == 'a')
            c[i] = '6';
        else if (c[i] == 'e')
            c[i] = '3';
        else if (c[i] == 'i')
            c[i] = '1';
        else if (c[i] == 'o')
            c[i] = '0';
        i++;
    }
    return (c);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Argument needed");
        return (1);
    }
    printf("%s\n", replace(argv[1]));
    return (0);
}