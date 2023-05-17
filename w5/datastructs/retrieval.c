#include <stdio.h>

typedef struct node
{
    char *number;  //no need to store char *name because each node will have 26 alphabets, each alphabet is a node which has 26 alphabets.
    struct node *alphabet[26];
} node;

node *tri; //pointer that points to starts of a tree;