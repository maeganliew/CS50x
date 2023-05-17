#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9

typedef struct
{
    string name;
    int votes;
}
candidate;

candidate candidates[MAX];
int candidate_count;

void print_winner(void)
{
    int max = candidates[0].votes;

    for (int i = 0; i + 1 < candidate_count; i++)
    {
        if (candidates[i + 1].votes > candidates[i].votes)
            max = candidates[i + 1].votes;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max)
            printf("%s\n", candidates[i].name);
    }
    return;
}

// Update vote totals given a new vote
bool vote(string name)
{
    for(int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
           candidates[i].votes += 1;
           //printf("%i", candidates[i].votes);
           return true;
        }
    }
    return false;
}

int main(int argc, string argv[])
{
    candidate_count = argc - 1;
    // Checking for specific cases (too less arguments?too many candidates)
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // Populate array of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    // Asking for no. of voters, getting votes
    int voter_count = get_int("Number of voters: ");
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");
        if (!vote(name))
            printf("Invalid vote.\n");
    }
    print_winner();
}