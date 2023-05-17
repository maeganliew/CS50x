#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int num;
    struct node *next;
} node;

int main(int argc, char *argv[])
{
    node *list = NULL;
    for (int i = 1; i < argc; i++)
    {
        int num = atoi(argv[i]);
        node *n = malloc(sizeof(node));
        n->num = num;
        n->next = NULL;
        n->next = list;
        list = n;
    }

    node *pointer = list;
    while (pointer != NULL) //while pointer is still pointing to valid address, still in the mid of the list
    {
        printf("%i\n", pointer -> num);
        pointer = pointer -> next; //continue pointing to the next node
    }
    //below is alternative
    /*
    for (node *pointer = list; pointer != NULL; pointer = pointer -> next)
        printf("%i", pointer -> num); */

    pointer = list; //basically to reset pointer to point at first node of the list
    while (pointer != NULL)
    {
        node *temp = pointer -> next; //store the *node of next node at temp
        free (pointer);
        pointer = temp;
    }
    return 0;
}