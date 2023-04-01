#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>



int main(void)
{
    typedef struct
{
    int winner;
    int loser;
}
pair;

pair pairs[5];

    for(int i = 0; i < 5; i++){
        pairs[i].winner = i + 1;
        pairs[i].loser = i + 1;
    }
        for(int i = 0; i < 5; i++){
        printf("pw: %i, pl: %i\n", pairs[i].winner, pairs[i].loser);
    }
    int strength[] = {5,4,3,2,1};
    int index;
    int compare;
    int temp_winner;
    int temp_loser;
    for(int i = 0; i < 5; i++){
        compare = strength[i];
        index = i;
        temp_winner = pairs[i].winner;
        temp_loser = pairs[i].loser;
        for(int j = 0; j < 5; j++){
            if(compare < strength[j]){
                compare = strength[j];
                index = j;
            }
        }
        if(index != i){
            pairs[i].winner = pairs[index].winner;
            pairs[i].loser = pairs[index].loser;
            pairs[index].winner = temp_winner;
            pairs[index].loser = temp_loser;
            strength[index] = strength[i];
        }
        strength[i] = 0;
    }

    for(int i = 0; i < 5; i++){
        printf("pw: %i, pl: %i\n", pairs[i].winner, pairs[i].loser);
    }
}