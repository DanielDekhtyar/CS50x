# Learning Python with CS50x
# DNA
# https://cs50.harvard.edu/x/2024/psets/6/dna/


import csv
import sys


def main():
    # Check for correct command-line usage
    check_if_argv_is_valid()

    # Open the DNA database CSV file
    dna_database = open_database_file()

    # Open the DNA sequence CSV file
    data_sequence = open_sequence_file()

    # Find longest match of each STR in DNA sequence
    STR_count = find_longest_match(dna_database, data_sequence)

    # Find which person the DNA belongs to
    name = check_database_for_match(dna_database, STR_count)

    print(name)

    return


def check_if_argv_is_valid() -> None:
    # Check for correct command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)


def open_database_file() -> list:
    # Open the DNA database CSV file
    with open(sys.argv[1], "r") as csvfile:
        reader = csv.DictReader(csvfile)
        dna_database = list(reader)

    return dna_database


def open_sequence_file() -> str:
    # Open the DNA sequence CSV file
    with open(sys.argv[2], "r") as txtfile:
        dna_sequence = txtfile.read()

    return dna_sequence


def find_longest_match(dna_database: list, dna_sequence: str) -> list:
    STR_count = {}
    for key in dna_database[0].keys():
        if key != "name":
            STR_count[key] = longest_match(dna_sequence, key)

    return STR_count


def check_database_for_match(dna_database: list, STR_count: list) -> str:
    for row in dna_database:
        if all(int(row[key]) == STR_count[key] for key in STR_count):
            return row["name"]

    return "No match"


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
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
