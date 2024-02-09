// Implements a dictionary's functionality
// Learning C with CS50x
// Speller
// https://cs50.harvard.edu/x/2024/psets/5/speller/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Represents the number of buckets in hash table
const unsigned int N = 26;

int dict_size = 0; // Global variable to store the number of words in the dictionary

// Hash table
node **table;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_index = hash(word);
    node *cursor = table[hash_index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false; // Return false if word is not found in the dictionary
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Ensure the first character is a letter
    if (!isalpha(word[0]))
    {
        return N; // Return an out-of-bounds index
    }

    // Convert the first character to uppercase and return its index
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Allocate memory for the hash table
    table = malloc(N * sizeof(node *));
    if (table == NULL)
    {
        return false;
    }
    
    // Initialize all elements of the hash table to NULL
    for (unsigned int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    // Create a new node for each word in the file
    char word[LENGTH + 1];
    while (fscanf(source, "%s", word) != EOF)
    {
        dict_size++; // Increment the dictionary size counter
        
        // Create a new node for the word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(source);
            return false;
        }

        // Copy the word into the node
        strcpy(n->word, word);

        // Calculate the hash index for the word
        int index = hash(word);

        // Insert the node at the beginning of the linked list
        n->next = table[index];
        table[index] = n;
    }

    // Close the dictionary file
    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size; // Return the number of words in the dictionary
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through the hash table and free each node
    for (unsigned int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        table[i] = NULL;
    }
    free(table);
    return true; // Return true if the hash table is unloaded successfully
}