#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string a = get_string("string: ");
    int b = strlen(a);
    int i;
    for(i=0; i<10; i++){
        if(a[i] == 65){
            printf("ha1\n");
        }
    }
}