#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2]; //to store blood type
} person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    srand(time(0));                            // Seed random number generator
    person *p = create_family(GENERATIONS);    //Create a new family with three generations
    print_family(p, 0);                        // Print family tree of blood types
    free_family(p);                            //free memory
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    person *human = malloc(sizeof(person));
    if (human == NULL)
        return NULL;

    if (generations > 1)  // If there are still generations left to create
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // TODO: Set parent pointers for current person
        human->parents[0] = parent0;
        human->parents[1] = parent1;
        // TODO: Randomly assign current person's alleles based on the alleles of their parents. one allele from one parents[0], one allele from parents[1]
        human->alleles[0] = human->parents[0]->alleles[rand() % 2];
        human->alleles[1] = human->parents[1]->alleles[rand() % 2];  //rand() % 2 returns number 0/1. if (rand%2 = 0), will choose alleles[0]
    }
    else
    {
        // TODO: Set parent pointers to NULL
        human->parents[0] = NULL;
        human->parents[1] = NULL;
        // TODO: Randomly assign alleles
        human->alleles[0] = random_allele();
        human->alleles[1] = random_allele();
    }
    // TODO: Return newly created person
    return human;
}

// Free `p` and all ancestors of `p`. this recursion will continue until base case reached, which is all parents freed. Then proceed to free child.
void free_family(person *p)
{
    // TODO: Handle base case
    if (p == NULL)
        return ;
    // TODO: Free parents recursively.
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // TODO: Free child
    free (p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
        return;

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
        printf(" ");

    // Print person
    if (generation == 0)
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    else if (generation == 1)
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    else
    {
        for (int i = 0; i < generation - 2; i++)
            printf("Great-");
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
        return 'A';
    else if (r == 1)
        return 'B';
    else
        return 'O';
}