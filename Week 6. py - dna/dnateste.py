import csv
import sys

def main():

    # TODO: Check for command-line usage
	if len(sys.argv) != 3:
		sys.exit("Usage: dna.py database.csv sequence.txt")

    # TODO: Read database file into a variable
	database = []
	with open(sys.argv[1]) as csvfile:
		reader = csv.DictReader(csvfile)
		for row in reader:
			database.append(row)

    # TODO: Read DNA sequence file into a variable
	with open(sys.argv[2]) as csvfile:
		dnasequence = csvfile.read()

    # TODO: Find longest match of each STR in DNA sequence
	allstrs = {}
	for key in database[0]:
		allstrs[key] = longest_match(dnasequence, key)
	allstrs.pop('name')

    # TODO: Check database for matching profiles
	for i in range(0,len(database)):
		found = True
		for key in allstrs:
			if int(database[i][key]) != int(allstrs[key]):
				found = False
				break
		if found:
			print(database[i]['name'])
			break

	if not found:
		print("No match")

def longest_match(dnasequence, pattern):

	count = 0
	add = pattern
	while pattern in dnasequence:
		count += 1
		pattern += add

	return count

main()
