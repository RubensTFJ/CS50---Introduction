#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

int main(int argc, string argv[])
{
    int a;
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

    int ranks[candidate_count];

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {

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
    for(int i = 0; i < candidate_count; i++){
        for(int j = 0; j < candidate_count; j++){
            printf("%i ", locked[i][j]);
            //printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }
    for(int i = 0; i < pair_count; i++){
    //printf("str: %i, srt: %i \n", strength[i]);
    }
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for(int i = 0; i < candidate_count; i++){
        if(strcmp(name, candidates[i]) == 0){
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for(int i = 0; i < candidate_count; i++){
        for (int j = i+1; j < candidate_count; j++){
            preferences[ranks[i]][ranks[j]] = preferences[ranks[i]][ranks[j]] +1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for(int i =0; i < (candidate_count - 1); i++){
        for(int j = (i + 1); j < candidate_count; j++){
            if(preferences[i][j] > preferences[j][i]){
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count = pair_count + 1;
            }
            else if(preferences[i][j] < preferences[j][i]){
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count = pair_count + 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int index;
    int compare;
    int temp_winner;
    int temp_loser;
    int strength[candidate_count];
    int counter;

    for(int i =0; i < (candidate_count - 1); i++){
        for(int j = (i + 1); j < candidate_count; j++){
            if(preferences[i][j] > preferences[j][i]){
                strength[counter] = preferences[i][j] - preferences[j][i];
                counter = counter + 1;
            }
            else if(preferences[i][j] < preferences[j][i]){
                strength[counter] = preferences[j][i] - preferences[i][j];
                counter = counter + 1;
            }
        }
    }

    for(int i = 0; i < candidate_count; i++){
        compare = strength[i];
        index = i;
        for(int j = i; j < candidate_count; j++){
            if(compare < strength[j]){
                compare = strength[j];
                index = j;
            }
        }
        if(index != i){
            temp_winner = pairs[index].winner;
            temp_loser = pairs[index].loser;
            for(int a = index; a > i; a--){
                pairs[a].winner = pairs[a-1].winner;
                pairs[a].loser = pairs[a-1].loser;
                strength[a] = strength[a-1];
            }
            pairs[i].winner = temp_winner;
            pairs[i].loser = temp_loser;
        }
        strength[i] = compare;
    }
    return;
}

bool cyclecheck(int winner, int loser){
    for(int i = 0; i < candidate_count; i ++){
        if(locked[loser][i] == true && i == winner){
            return true;
        }
        else if(locked[loser][i] == true && cyclecheck(winner, i) == true){
            return true;
        }
    }
    return false;
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int winner;
    int loser;
    for(int i = 0; i < pair_count; i++){
        winner = pairs[i].winner;
        loser = pairs[i].loser;
        if(cyclecheck(winner, loser) == false){
        locked[winner][loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool winnable[candidate_count];
    for(int i = 0; i < candidate_count; i ++){
    winnable[i] = true;
    }

    for(int i = 0; i < candidate_count; i++){
        for(int j = 0; j < candidate_count; j++){
            if(locked[i][j] == true){
                winnable[j] = false;
            }
        }
    }

    for(int i = 0; i < candidate_count; i++){
        if(winnable[i] == true){
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
