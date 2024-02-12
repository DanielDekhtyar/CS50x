# Learning Python with CS50x
# Credit
# https://cs50.harvard.edu/x/2024/psets/6/credit/


import re


def main():
    credit_card_number = int(input("Number: "))
    if not is_valid_credit_card_number(credit_card_number):
        print("INVALID")

    else:
        print(credit_card_company_name(credit_card_number))


def is_valid_credit_card_number(credit_card_number: int):
    # Get the length of the credit card number
    card_number_length = len(str(credit_card_number))

    valid_card_lengths = [13, 15, 16]

    # Check that the credit card number is exactly 16 characters
    if card_number_length not in valid_card_lengths:
        return False

    credit_card_number = str(credit_card_number)

    nDigits = len(credit_card_number)
    nSum = 0
    isSecond = False

    for i in range(nDigits - 1, -1, -1):
        d = ord(credit_card_number[i]) - ord("0")

        if isSecond == True:
            d = d * 2

        # We add two digits to handle
        # cases that make two digits after
        # doubling
        nSum += d // 10
        nSum += d % 10

        isSecond = not isSecond

    if nSum % 10 == 0:
        return True
    else:
        return False


def credit_card_company_name(credit_card_number: int) -> str:
    # Get the length of the credit card number
    card_number_length = len(str(credit_card_number))
    # Get the first two digits of the credit card number
    first_two_digits = str(credit_card_number)[0:2]

    # Check if the credit card number is a valid Visa card
    if (card_number_length == 13 or card_number_length == 16) and (
        first_two_digits[:1] == "4"
    ):
        return "VISA"

    # Check if the credit card number is a valid Mastercard card
    if (card_number_length == 16) and (
        first_two_digits == "51"
        or first_two_digits == "52"
        or first_two_digits == "53"
        or first_two_digits == "54"
        or first_two_digits == "55"
    ):
        return "MASTERCARD"

    # Check if the credit card number is a valid American Express card
    if (card_number_length == 15) and (
        first_two_digits == "34" or first_two_digits == "37"
    ):
        return "AMEX"
    else:
        return "INVALID"


if __name__ == "__main__":
    main()
