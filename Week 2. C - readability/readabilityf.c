#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

struct gatherdata(string text);

typedef struct{
    float words;
    int letters;
    int sentences;
}
data;

int main(void)
{
    data datas[3];
    float l;
    float s;
    float index;
    string text = get_string("Insert Text: ");
    printf("%f words, %i letter, %i sentences.\n", datas[0].words, datas[0].letters, datas[0].sentences);
    datas = gatherdata(text);
    printf("%f words, %i letter, %i sentences.\n", datas[0].words, datas[0].letters, datas[0].sentences);

    l = datas[0].letters/datas[0].words*100.0;
    s = datas[0].sentences/datas[0].words*100.0;
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

struct gatherdata(string text)
{
    data datas[3];
    int i;
    int length = strlen(text);
    bool ground = true;
    bool hole = true;
    datas[0].letters = 0;
    datas[0].sentences = 0;
    datas[0].words = 0;

    for(i = 0; i< length; i++){
        text[i] = toupper(text[i]);
        if(65 <= text[i] && text[i] <= 90){
            datas[0].letters = datas[0].letters + 1;
            ground = true;
        }
        else if(text[i] == 33 || text[i] == 46 || text[i] == 63){
            datas[0].sentences = datas[0].sentences + 1;
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
            datas[0].words = datas[0].words + 1;
            hole = false;
        }
    }
    return datas;
}

