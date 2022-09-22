#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool makes_cycle(int start, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++) //for to check if the candidate is on the array
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i; //Sets the rank to its respective candidate position on the array of candidates
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int ipos = 0; //variable to know where is the candidate i
            int jpos = 0; //variable to know where is the candidate j
            for (int z = 0; z < candidate_count; z++) //checks for candidate position in array ranks
            {
                if (i == ranks[z])
                {
                    ipos = z;
                }
                if (j == ranks[z])
                {
                    jpos = z;
                }
            }
            if (ipos < jpos)
            {
                preferences[i][j] += 1;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //Checks for possible combinations if one is bigger than the other inversing the index
    //That is how it actually compares it one candidate to another based on the 2D preferences array
    //Saves the winner and loser candidate index
    //Adds 1 each time it finds a difference
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int swap = 0;
    int w1 = 0;
    int w2 = 0;
    int l1 = 0;
    int l2 = 0;
    do //Bubble sort
    {
        swap = 0;
        for (int i = -1; i < pair_count - 2; i++) //added winner and loser to keep the pairs logic
        {
            w1 = pairs[i + 1].winner;
            w2 = pairs[i + 2].winner;
            l1 = pairs[i + 1].loser;
            l2 = pairs[i + 2].loser;

            //Comparing values on the preferences 2D array since it keeps the total preferences from the voters
            if (preferences[pairs[i + 1].winner][pairs[i + 1].loser] < preferences[pairs[i + 2].winner][pairs[i + 2].loser])
            {
                pairs[i + 1].winner = w2;
                pairs[i + 1].loser = l2;
                pairs[i + 2].winner = w1;
                pairs[i + 2].loser = l1;
                swap += 1;
            }
        }
    }
    while (swap != 0);
    return;
}

// Lock pairs into the candidate graph in order starting with the strongest victory, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!makes_cycle(pairs[i].winner, pairs[i].loser)) //Will add a true if it does not create a cycle
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}


// Print the winner of the election
void print_winner(void)
{
    //This needs to be equal to the number of candidates to be the source of the graph
    int winner_count;
    //will save the position on the candidate array from the winner
    int winner = 0;
    //Cycle to check column by column who accumulates 3 false statements
    for (int i = 0; i < candidate_count; i++)
    {
        winner_count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (!locked[j][i])
            {
                winner_count++;
            }
            if (winner_count == candidate_count)
            {
                winner = i;
                break;
            }
        }
    }
    printf("%s\n", candidates[winner]);

    return;
}


bool makes_cycle(int start, int loser)
{
    if (loser == start) //If loser is pointing winner
    {
        return true;
    }
    //Evaluates the function in all columns of the locked function with given loser row
    //If there is a true then it would call the function again changing the row to the column found
    //And it would evaluate if there is a true on the same place than the loser
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (makes_cycle(start, i))
            {
                return true;
            }
        }
    }
    return false;
}
