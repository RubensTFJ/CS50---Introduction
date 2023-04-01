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

	with open(sys.argv[1]) as csvfile:
		reader = csv.reader(csvfile)
		header = next(reader)
	header.pop(0)

    # TODO: Read DNA sequence file into a variable
	with open(sys.argv[2]) as csvfile:
		dnasequence = csvfile.read()

    # TODO: Find longest match of each STR in DNA sequence
	allstrs = []
	for i in range(0,len(header)):
		allstrs.append(longest_match(dnasequence, header[i]))

    # TODO: Check database for matching profiles
	found = -1
	for i in range(0,len(database)):
		j = 0
		count = 0
		loop = True
		while loop == True and j < len(allstrs):
			if int(database[i][header[j]]) == allstrs[j]:
				count += 1
			else:
				loop = False
			j += 1
		if count == (len(allstrs)):
			found = i
			break
	if found == -1:
		print("No match")
	else:
		print(database[found]['name'])



def longest_match(dnasequence, pattern):

	count = 0
	add = pattern
	while pattern in dnasequence:
		count += 1
		pattern += add

	return count

main()



    # """Returns length of longest run of subsequence in sequence."""

    # # Initialize variables
    # longest_run = 0
    # subsequence_length = len(subsequence)
    # sequence_length = len(sequence)

    # # Check each character in sequence for most consecutive runs of subsequence
    # for i in range(sequence_length):

    #     # Initialize count of consecutive runs
    #     count = 0

    #     # Check for a subsequence match in a "substring" (a subset of characters) within sequence
    #     # If a match, move substring to next potential match in sequence
    #     # Continue moving substring and checking for matches until out of consecutive matches
    #     while True:

    #         # Adjust substring start and end
    #         start = i + count * subsequence_length
    #         end = start + subsequence_length

    #         # If there is a match in the substring
    #         if sequence[start:end] == subsequence:
    #             count += 1

    #         # If there is no match in the substring
    #         else:
    #             break

    #     # Update most consecutive matches found
    #     longest_run = max(longest_run, count)

    # # After checking for runs at each character in seqeuence, return longest run found
    # return longest_run


