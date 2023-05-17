// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *hashtable[N];

//count words;
unsigned int wordcount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int bucket = hash(word);
    node *cursor = hashtable[bucket];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
            return true;
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int ascii = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
        ascii += toupper(word[i]);
    return (ascii % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    char word[LENGTH+1];
    while(fscanf(file, "%s", word) != EOF) //EOF == end of file
    {
        node *new = malloc(sizeof(node));  //need to malloc space for a whole new node!! not only for word
        if (new == NULL)
            return false;
        strcpy(new->word, word);

        unsigned int bucket = hash(word);
        new->next = hashtable[bucket]; //only hashtable[bucket]! not hashtable[bucket]->next(seg fault). hashtable[bucket] is already pointing
        hashtable[bucket] = new;
        wordcount++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (wordcount > 0)
        return wordcount;
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}