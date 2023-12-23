// Learning C with CS50x
// Readability
// https://cs50.harvard.edu/x/2024/psets/2/readability/

#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int letterCount(string s);
int wordCount(string s);
int sentenceCount(string s);

int main(void)
{
    string str = get_string("Give me a string: ");
    double l = 100.0 * letterCount(str) / wordCount(str); // Average number of letters per 100 words
    double s = 100.0 * sentenceCount(str) / wordCount(str); // Average number of sentences per 100 words
    double Grade = 0.0588 * l - 0.296 * s - 15.8;

    if (Grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (Grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)round(Grade));
    }
}

int letterCount(string s)
{
    int l = 0; // Count the number of letters
    for (int i = 0, slen = strlen(s); i < slen; i++)
    {
        if (isalpha(s[i]))
        {
            l++;
        }
    }
    return l;
}

int wordCount(string s)
{
    int w = 0; // Word count
    for (int i = 0, slen = strlen(s); i < slen; i++)
    {
        if (isspace(s[i]))
        {
            w++;
        }
    }
    return w + 1; // Add 1 at the end because the last word doesn't have a space after it
}

int sentenceCount(string s)
{
    int sentence = 0;
    for (int i = 0, slen = strlen(s); i < slen; i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentence++;
        }
    }
    if (sentence == 0)
    {
        sentence++;
    }
    return sentence;
}
