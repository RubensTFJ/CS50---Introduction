# TODO

def main():

    valid = False
    while valid == False:
        try:
            card = input("Insert Card Number: ")
            test = int(card)
            valid = True
        except:
            valid = False

    result = sumcheck(card)
    if result == True:
        typecheck(card)

def sumcheck(card):

    cardlen = len(card) -1
    sum = 0
    sum2 = 0
    for i in range(cardlen,-1,-2):
        sum2 += int(card[i])
        if i-1 > -1:
            if int(card[i-1]) > 4:
                n = str(int(card[i-1])*2)
                sum += int(n[0]) + int(n[1])
            else:
                sum += 2*int(card[i-1])

    last = (sum + sum2) % 10
    if last == 0:
        return True
    else:
        print("INVALID")
        return False

def typecheck(card):

    if 4*pow(10,12) <= int(card) < 5*pow(10,12):
        print("VISA")
    elif (34*pow(10,13) <= int(card) < 35*pow(10,13)) or (37*pow(10,13) <= int(card) < 38*pow(10,13)):
        print("AMEX")
    elif 51*pow(10,14) <= int(card) < 56*pow(10,14):
        print("MASTERCARD")
    elif 4*pow(10,15) <= int(card) < 5*pow(10,15):
        print("VISA")
    else:
        print("INVALID")

main()