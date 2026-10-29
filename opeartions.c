#include "inverted_search.h"


// Function to initialize the hash table
void initialize_database(hash_t *hash_table)
{
    int i;

    // Traverse all the hash table buckets
    for (i = 0; i < SIZE; i++)
    {
        // Store the bucket index
        hash_table[i].index = i;

        // Initially, every bucket is empty
        hash_table[i].main_link = NULL;
    }
}