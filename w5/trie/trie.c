// Saves popular dog names in a trie
// https://www.dailypaws.com/dogs-puppies/dog-names/common-dog-names

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_ALPHABET 26
#define MAXCHAR 20

typedef struct node
{
    bool is_word;
    struct node *children[SIZE_OF_ALPHABET];
} node;

bool check(char *word);
bool unload(void);
void unloader(node *current);

node *root;
char name[MAXCHAR];

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./trie infile\n");
        return 1;
    }

    // File with names
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    // Allocate root of trie
    root = malloc(sizeof(node));
    if (root == NULL)
        return 1;

    root->is_word = false; //initialising the node, set bool to false, array of nodes to NULL
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
        root->children[i] = NULL;

    //filling the trie
    while (fscanf(infile, "%s", name) == 1) //filling strings of names to buffer "name", one string each time
    {
        node *cursor = root;
        for (int i = 0, n = strlen(name); i < n; i++)
        {
            int index = tolower(name[i]) - 'a'; //index is actually the position of current character in array of nodes "children"
            if (cursor->children[index] == NULL)
            {
                // Make node. whole chunk is creating new "nodes", each node has a "children" array with 26 nodes
                node *new = malloc(sizeof(node));
                new->is_word = false;
                for (int j = 0; j < SIZE_OF_ALPHABET; j++)
                    new->children[j] = NULL;
                cursor->children[index] = new;
            }
            // Go to node which we may have just been made
            cursor = cursor->children[index];
        }
        // if we are at the end of the word, mark it as being a word
        cursor->is_word = true;
    }

    if (check(get_string("Check word: ")))
        printf("Found!\n");
    else
        printf("Not Found.\n");

    if (!unload())
    {
        printf("Problem freeing memory!\n");
        return 1;
    }
    fclose(infile);
}

// TODO: Complete the check function, return true if found, false if not found
bool check(char* word)
{
    node *cursor = root;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        int index = tolower(word[i]) - 'a';
        if (cursor->children[index] != NULL)
            cursor = cursor->children[index];
        else
            return false;
    }
    cursor->is_word = true;
    return true;
}

// Unload trie from memory
bool unload(void)
{
    // The recursive function handles all of the freeing
    unloader(root);
    return true;
}

void unloader(node* current)
{
    // Iterate over all the children to see if they point to anything and go there if they do point
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        if (current->children[i] != NULL)
            unloader(current->children[i]);
    }
    // After we check all the children point to null we can get rid of the node
    // and return to the previous iteration of this function.
    free(current);
}
