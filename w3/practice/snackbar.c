/**
 * Beach Burger Shack has the following 10 items on their menu
 * Burger: $9.5
 * Vegan Burger: $11
 * Hot Dog: $5
 * Cheese Dog: $7
 * Fries: $5
 * Cheese Fries: $6
 * Cold Pressed Juice: $7
 * Cold Brew: $3
 * Water: $2
 * Soda: $2
*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#define NUM_ITEMS 10

typedef struct
{
    string item;
    float price;
}
menu_item;

menu_item menu[NUM_ITEMS];

void add_items(void)
{
    menu[0].item = "burger";
    menu[0].price = 9.5;

    menu[1].item = "vegan burger";
    menu[1].price = 11;

    menu[2].item = "hot dog";
    menu[2].price = 5;

    menu[3].item = "cheese dog";
    menu[3].price = 7;

    menu[4].item = "fries";
    menu[4].price = 5;

    menu[5].item = "cheese fries";
    menu[5].price = 6;

    menu[6].item = "cold pressed juice";
    menu[6].price = 7;

    menu[7].item = "cold brew";
    menu[7].price = 3;

    menu[8].item = "water";
    menu[8].price = 2;

    menu[9].item = "soda";
    menu[9].price = 2;
    return;
}

float get_cost(string item)
{
    for (int i = 0; i < 10; i++)
    {
        if (strcmp(item,menu[i].item) == 0)
            return (menu[i].price);
    }
    return (0.0);
}

int main(void)
{
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
        printf("%s: $%.2f\n", menu[i].item, menu[i].price);
    printf("\n");

    float total = 0;
    while (true)
    {
        string item = get_string("Enter a food item: ");
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }
        for (int i = 0; i < strlen(item); i++)
            item[i] = tolower(item[i]);
        total += get_cost(item);
    }
    printf("Your total cost is: $%.2f\n", total);
}