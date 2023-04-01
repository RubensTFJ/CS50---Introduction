# TODO

text = input("Insert Text: ")

letters = 0
for char in text:
    if char.isalpha():
        letters += 1

setences = text.count(".") + text.count("!") + text.count("?")
wordlist = text.split()
words = len(wordlist)

l = letters/words*100
s = setences/words*100
index = round(0.0588*l - 0.296*s - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 15:
    print("Grade 16+")
else:
    print(f"Grade {index}")

