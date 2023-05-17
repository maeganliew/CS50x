#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit)
{
    if (bit == 0)
        printf("\U000026AB"); //dark emoji
    else if (bit == 1)
        printf("\U0001F7E1"); //light emoji
}

int main(void)
{
    string str = get_string("Message: ");
    int n = strlen(str);
    int i = 0;
    int ascii = 0;

    while (i < n)
    {
        ascii = str[i];
        int power = BITS_IN_BYTE - 1;
        while (power >= 0)
        {
            print_bulb(ascii/ (int)pow(2,power));
            if (ascii / (int)pow(2,power) == 1)
                ascii -= pow(2,power);
            power--;
        }
        printf("\n");
        i++;
    }
}
