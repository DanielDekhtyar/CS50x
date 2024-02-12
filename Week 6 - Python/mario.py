# Learning Python with CS50x
# Mario
# https://cs50.harvard.edu/x/2024/psets/6/mario/more/


import cs50


def main():
    while True:
        height = cs50.get_int("Height: ")
        if height >= 1 and height <= 8:
            break

    for row in range(height):
        print(" " * (height - row - 1), end="")
        print("#" * (row + 1), end="")
        print("  ", end="")
        print("#" * (row + 1))


if __name__ == "__main__":
    main()
