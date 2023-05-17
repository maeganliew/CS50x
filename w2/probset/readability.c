#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int calc_letters(string str)
{
    int n = 0;
    int i = 0;
    while (str[i])
    {
        if (isupper(str[i]) || islower(str[i]))
            n++;
        i++;
    }
    return (n);
}

int calc_words(string str)
{
    int n = 1;
    int i = 0;
    while (str[i])
    {
        if (str[i] == ' ')
            n++;
        i++;
    }
    return (n);
}

int calc_sent(string str)
{
    int n = 0;
    int i = 0;
    while (str[i])
    {
        if (str[i] == '!' || str[i] == '.' || str[i] == '?')
            n++;
        i++;
    }
    return (n);
}

int calc_grade(string str)
{
    int letters = calc_letters(str);
    int words = calc_words(str);
    int sent = calc_sent(str);

    float L = (float) letters/words*100;
    float S = (float) sent/words*100;
    float grade = 0.0588 * L - 0.296 * S - 15.8;
    int roundup = round(grade);
    return (roundup);
}

int main(void)
{
    string text = get_string("Text: ");
    int n = calc_grade(text);
    if (n < 1)
        printf("Before Grade 1");
    else if (n >= 16)
        printf("Grade 16+");
    else printf("Grade %i", n);
    printf("\n");
}