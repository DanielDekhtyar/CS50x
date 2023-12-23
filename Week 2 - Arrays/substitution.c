// Learning C with CS50x
// Substitution
// https://cs50.harvard.edu/x/2024/psets/2/substitution/

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void isValid(int argc, string argv[]);
void makeUpper(string argv[]);
string encipher(string argv[], string str);
char substitution(string argv[], char ch);

int main(int argc, string argv[])
{
    isValid(argc, argv);
    makeUpper(argv);
    string str = get_string("Plain text: ");
    string enciphered = encipher(argv, str);
    printf("ciphertext: %s\n", enciphered);
}

void isValid(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        exit(1);
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        exit(1);
    }

    makeUpper(argv);

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            exit(1);
        }
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        int same = 0; // Count how many same characters there are
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            if (argv[1][j] == argv[1][i])
            {
                same++;
            }
        }
        if (same > 1)
        {
            printf("Key must not contain repeated characters.\n");
            exit(1);
        }
    }
}

void makeUpper(string argv[])
{
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        argv[1][i] = toupper(argv[1][i]);
    }
}

string encipher(string argv[], string str)
{
    string ciphered = malloc((strlen(str) + 1) * sizeof(char));
    for (int i = 0; i < strlen(str); i++)
    {
        ciphered[i] = substitution(argv, str[i]);
        if (islower(str[i]))
        {
            ciphered[i] = tolower(ciphered[i]);
        }
    }
    return ciphered;
}

char substitution(string argv[], char ch)
{
    if (isalpha(ch))
    {
        ch = toupper(ch);
        int ascii = ch;
        ch = argv[1][ascii - 65];
    }
    return ch;
}
