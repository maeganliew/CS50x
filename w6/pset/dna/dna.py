import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Invalid Usage")
        sys.exit(1)


    # TODO: Read database file into a variable
    database = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)    #dictreader converts each row in file to dict of key value pairs
        for row in reader:
            database.append(row)


    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        sequence = file.read()   #only reading a line of text


    # TODO: Find longest match of each STR in DNA sequence
    strs = list(database[0].keys())[1:]  #typecast to list,keys() will return keys of dict as a list. adding [1:] at end of typecast means list start storing from the 1st key, not 0th key(excluding "name")
    match_num = {}
    for i in strs:
        match_num[i] = longest_match(sequence, i)  #a dict called match_num, keys are the elemets of "strs" list, respective values will be longest match of each str


    # TODO: Check database for matching profiles
    for n in database:     #looping through each person(dict) in the list called database
        count = 0
        for i in strs:
            if int(n[i]) == match_num[i]:   #typecast database numbers to integers! they were read as strings
                count += 1
        if count == len(strs):  #which means all str in list "strs" are matched
            print(n["name"])    #why no need to add f""????? like print(f"{n["name"]}"). f"" only when printing variables.
            return
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:  #check characters from start to end in sequence
                count += 1

            # If there is no match in the substring
            else:
                break  #i will then increment, cuz broke out of while True:

        # Update most consecutive matches found
        longest_run = max(longest_run, count)   #updating value of longest_run throught out the whole sequence

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()