# Learning Python with CS50x
# Readability
# https://cs50.harvard.edu/x/2024/psets/6/readability/


def main():
    text = input("Text: ")
    average_number_of_letters = 100 * letter_count(text) / word_count(text)
    average_number_of_sentences = 100 * sentences_cont(text) / word_count(text)

    grade = (
        (0.0588 * average_number_of_letters)
        - (0.296 * average_number_of_sentences)
        - 15.8
    )
    print(grade)

    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(grade)}")


def letter_count(text):
    count = 0
    for char in text:
        if char.isalpha():
            count += 1

    return count


def word_count(text):
    num_words = 1

    for char in text:
        if char == " ":
            num_words += 1

    return num_words


def sentences_cont(text):
    num_sentences = 0

    for char in text:
        if char == "." or char == "!" or char == "?":
            num_sentences += 1

    return num_sentences


if __name__ == "__main__":
    main()
