#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int gatherdata(string text);

int main(void)
{
    int i;
    bool ground = true;
    bool hole = true;
    float words = 0;
    int letters = 0;
    int setences = 0;
    float l;
    float s;
    float index;
    string text = get_string("Insert Text: ");
    int length = strlen(text);

    for(i = 0; i< length; i++){
        text[i] = toupper(text[i]);
        if(65 <= text[i] && text[i] <= 90){
            letters = letters + 1;
            ground = true;
        }
        else if(text[i] == 33 || text[i] == 46 || text[i] == 63){
            setences = setences + 1;
            hole = true;
            ground = false;
        }
        else if(text[i] == 39 || text[i] == 45){
            ground = true;
        }
        else{
            hole = true;
            ground = false;
        }
        if(ground == true && hole == true){
            words = words + 1;
            hole = false;
        }
    }
    l = letters/words*100.0;
    s = setences/words*100.0;
    index = 0.0588*l - 0.296*s - 15.8;
    index = round(index);

    if(index < 1){
        printf("Before Grade 1\n");
    }
    else if(index > 15){
        printf("Grade 16+\n");
    }
    else{
    //printf("s: %f, l: %f, index: %i\n", s, l, index);
    printf("Grade %.f\n", index);
    }
}



