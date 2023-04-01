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
    int strength[] = {1,2,3,4,5};
    int index;
    int compare;
    int temp_winner;
    int temp_loser;
    for(int i = 0; i < 5; i++){
        compare = strength[i];
        index = i;
        temp_winner = pairs[i].winner;
        temp_loser = pairs[i].loser;
        for(int j = i; j < 5; j++){
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

    for(int i = 0; i < 5; i++){
        printf("pw: %i, pl: %i\n", pairs[i].winner, pairs[i].loser);
    }
}