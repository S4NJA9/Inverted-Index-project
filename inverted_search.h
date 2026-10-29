#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

// Standard input and output functions
#include <stdio.h>
// Memory allocation functions
#include <stdlib.h>
// String handling functions
#include <string.h>
// Character handling functions
#include <ctype.h>
// Total number of hash table buckets
#define SIZE 27
// Return values
#define SUCCESS 1
#define FAILURE 0

// Structure for the sub-node
typedef struct sub_node
{
    // Number of times a word appears in a file
    int word_count;
    // Name of the file
    char filename[100];
    // Link to the next sub-node
    struct sub_node *sub_link;
} sub_t;

// Structure for the main-node
typedef struct main_node
{
    // Number of files containing the word
    int file_count;
    // Stores the unique word
    char word[100];
    // Link to the first sub-node
    sub_t *sub_link;\
    // Link to the next main-node
    struct main_node *main_link;
} main_t;


// Structure for the hash table
typedef struct hash
{
    // Hash table bucket index
    int index;
    // Link to the first main-node
    main_t *main_link;
} hash_t;

// Structure for the doubly linked list
typedef struct dlist
{
    // Name of the input file
    char filename[100];
    // Link to the previous node
    struct dlist *prev;
    // Link to the next node
    struct dlist *next;
} Dlist;


// Function declarations
int file_handling(Dlist **head, Dlist **tail, char *argv[]);
void initialize_database(hash_t *hash_table);
void print_menu(void);
void display_database(hash_t *hash_table);
int create_database(hash_t *arr, int size, Dlist *head, Dlist *tail);
int search_database(hash_t *arr);
int save_database(hash_t *hash_table);
int update_database(hash_t *hash_table);

#endif