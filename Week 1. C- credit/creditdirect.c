#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long card;
    int i;
    long n;
    int sum;
    int sum2 = 0;
    int last;
    long elevar;
    long card2;

    card = get_long("Insert Card Number: \n");
    card2 = card;

    for(i=0; i<16; i++){
        elevar = pow(10,(i+1));
        n = (card % elevar);
        sum2 = sum2 + (n/pow(10,i));
        card = card - n;

        i = i + 1;
        elevar = pow(10,(i+1));
        n = (card % elevar);
        card = card - n;
        n = 2*(n/pow(10,i));
        if(n >= 10){
            sum = sum + 1 + (n % 10);
        }
        else{
            sum = sum + (n);
        }
    }

    last = (sum + sum2) % 10;
    if(last !=0){
        printf("INVALID.\n");
    }
    else if(4*pow(10,12) <= card2 && card2 < 5*pow(10,12)){
    printf("VISA\n");
    }
    else if((34*pow(10,13) <= card2 && card2 < 35*pow(10,13)) || (37*pow(10,13) <= card2 && card2 < 38*pow(10,13))){
    printf("AMERICANEXP\n");
    }
    else if(51*pow(10,14) <= card2 && card2 < 56*pow(10,14)){
    printf("MASTERCARD\n");
    }
    else if(4*pow(10,15) <= card2 && card2 < 5*pow(10,15)){
    printf("VISA\n");
    }
    else{
    printf("INVALID\n");
    }
}