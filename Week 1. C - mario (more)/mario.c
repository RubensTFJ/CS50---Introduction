#include <cs50.h>
#include <stdio.h>

int main(void)
{
    void spaces(int n);
    void hashes(int n);
    int height;

    // Get Pyramid Height from user.
    do
    {
    height = get_int("Insert pyramid height: ");
    }
    while(height<=0 || height>8);

    //Print Spaces and Hashes on a loop by calling the function Spaces and Hashes.
    for(int i=0; i<height; i++)
    {
        /*The number of spaces is increasely smaller because the number of
        Hashes increases in each line*/
        spaces(height-i);
        hashes(i);
    }
}

/* Receives an Argument and prints one less Space than received because the
last digits are Hashes */
void spaces(int n)
{
    for(int i = 1; i<n; i++)
    {
    printf(" ");
    }
}

//Receives an Argument and Prints That many Hahses Twice, separated by two spaces.
void hashes(int n)
{
    for (int i=0; i<=n; i++)
    {
        printf("#");
    }
    printf("  ");
    for (int i=0; i<=n; i++)
    {
        printf("#");
    }
    printf("\n");
}
