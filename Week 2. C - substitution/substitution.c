#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int i;
    int j;
    int arguments = 0;
    string key = argv[1];

    for(i = 0; argv[i] != NULL; i++){
        arguments = arguments + 1;
    }
    if(arguments != 2){
        printf("Usage: ./substitution key\n");
        return 1;
    }
    int length = strlen(argv[1]);
    if(length != 26){
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string loweralpha = {"abcdefghijklmnopqrstuvwxyz"};
    string upperalpha = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    char upperkey[26];
    char lowerkey[26];
    for(i = 0; i < 26 ; i++){
        upperkey[i] = toupper(argv[1][i]);
        lowerkey[i] = tolower(argv[1][i]);
    }
    for(i = 0; i < length; i++){
        for(j = 0; j < length; j++){
            if(argv[1][i] == key[j] && i != j){
                return 1;
            }
            else if(upperkey[i] < 65 || upperkey[i] > 90){
                return 1;
            }
        }
    }

    int check;

    string plain = get_string("Plain text: ");
    length = strlen(plain);

    for(i = 0; i < length; i++){
        check = isupper(plain[i]);
        if(check != 0){
            for(j = 0; j < 26; j++){
                if(plain[i] == upperalpha[j]){
                    plain[i] = upperkey[j];
                    j = 26;
                }
            }
        }
        else{
            for(j = 0; j < 26; j++){
                if(plain[i] == loweralpha[j]){
                    plain[i] = lowerkey[j];
                    j = 26;
                }
            }
        }
    }

    printf("ciphertext: %s\n", plain);

}