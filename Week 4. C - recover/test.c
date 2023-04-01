#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

int test();

int main(void)
{
    int numero = 1;
    char name[7];
    sprintf(name, "%03i.jpg", numero);
    printf("%s.\n", name);
}

/*
int test(int a)
{
    if(a == 0xff)
    {
        return 1;
    }

    return 0;
}
*/