#include <cs50.h>
#include <stdio.h>
#include <math.h>

bool sumcheck(long card);
void typecheck(long card);

int main(void)
{
    long card;
    bool result;

    card = get_long("Insert Card Number: \n");
    result = sumcheck(card);
    if(result == true){
        typecheck(card);
    }

}

bool sumcheck(long card){
    int i;
    long power;
    long n;
    int sum = 0;
    int sum2 = 0;
    int last;

    for(i=0; i<16; i++){
        power = pow(10,(i+1));
        n = (card % power);
        sum2 = sum2 + (n/pow(10,i));
        card = card - n;

        i = i + 1;
        power = pow(10,(i+1));
        n = (card % power);
        card = card - n;
        n = 2*(n/pow(10,i));
        if(n >= 10)
            sum = sum + 1 + (n % 10);
        else
            sum = sum + (n);
    }
    last = (sum + sum2) % 10;
    if(last == 0)
        return true;
    else
        printf("INVALID\n");
        return false;
}

void typecheck(long card){
    if(4*pow(10,12) <= card && card < 5*pow(10,12)){
    printf("VISA\n");
    }
    else if((34*pow(10,13) <= card && card < 35*pow(10,13)) || (37*pow(10,13) <= card && card < 38*pow(10,13))){
    printf("AMEX\n");
    }
    else if(51*pow(10,14) <= card && card < 56*pow(10,14)){
    printf("MASTERCARD\n");
    }
    else if(4*pow(10,15) <= card && card < 5*pow(10,15)){
    printf("VISA\n");
    }
    else{
    printf("INVALID\n");
    }
}