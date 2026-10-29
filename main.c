/*
 ============================================================================
 Name        : main.c
 Author      : Sanjay Hibare
 Date        : 14-09-2026
 Project     : Inverted Search

 Description :
     This project creates and manages an inverted database from multiple
     text files.

     The database stores every unique word and the files in which that word
     appears. It also stores the number of occurrences of the word in each
     file.

     The project uses:
         1. Hash table
         2. Doubly linked list
         3. File handling
         4. Dynamic memory allocation

     Menu operations:
         1. Create database
         2. Display database
         3. Update database
         4. Search database
         5. Save database
         6. Exit
 ============================================================================
*/

#include "inverted_search.h"

// Function declarations
int validation(int argc);
int continue_or_exit(void);

// Function to validate command-line arguments
int validation(int argc)
{
    // Check whether input files are provided
    if (argc < 2)
    {
        printf("\nERROR: Please provide input files.\n");
        printf("Usage: ./inverted_search file1.txt file2.txt ...\n");

        return FAILURE;
    }

    return SUCCESS;
}

// Function to ask whether the user wants to continue
int continue_or_exit(void)
{
    char choice;

    while (1)
    {
        printf("\nDo you want to continue?\n");
        printf("Enter y/Y to continue\n");
        printf("Enter n/N to discontinue\n");
        printf("Enter your choice: ");

        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y')
        {
            return SUCCESS;
        }
        else if (choice == 'n' || choice == 'N')
        {
            printf("\nProgram discontinued.\n");

            return FAILURE;
        }
        else
        {
            printf("\nInvalid choice. Please enter y/Y or n/N.\n");
        }
    }
}

// Main function
int main(int argc, char *argv[])
{
    hash_t hash_table[SIZE];

    int choice;

    Dlist *head = NULL;
    Dlist *tail = NULL;

    // Validate command-line arguments
    if (validation(argc) == FAILURE)
    {
        return FAILURE;
    }

    // Validate files and store them in the linked list
    file_handling(&head, &tail, argv);

    // Initialize the hash table
    initialize_database(hash_table);

    // Display menu until the user exits
    do
    {
        print_menu();

        // Read menu choice
        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input. Please enter a number from 1 to 6.\n");

            // Clear invalid input
            while (getchar() != '\n')
            {
            }

            continue;
        }

        switch (choice)
        {
        case 1:
            printf("\nCreate database selected.\n");

            // Create the inverted database
            if (create_database(hash_table, SIZE, head, tail) == SUCCESS)
            {
                printf("\nCreation of database completed successfully.\n");
            }
            else
            {
                printf("\nERROR: Database creation failed.\n");
            }

            if (continue_or_exit() == FAILURE)
            {
                return SUCCESS;
            }

            break;

        case 2:
            printf("\nDisplay database selected.\n");

            // Display the inverted database
            display_database(hash_table);

            if (continue_or_exit() == FAILURE)
            {
                return SUCCESS;
            }

            break;

        case 3:
            printf("\nUpdate database selected.\n");
            if (update_database(hash_table) == SUCCESS)
            {
                printf("\nDatabase updated successfully.\n");
            }
            else
            {
                printf("\nERROR: Database update failed.\n");
            }
            if (continue_or_exit() == FAILURE)
            {
                return SUCCESS;
            }
            break;

        case 4:
            printf("\nSearch database selected.\n");

            // Search for a word
            if (search_database(hash_table) == SUCCESS)
            {
                printf("\nWord search completed successfully.\n");
            }

            if (continue_or_exit() == FAILURE)
            {
                return SUCCESS;
            }

            break;

        case 5:

            printf("\nSave database selected.\n");

            if (save_database(hash_table) == SUCCESS)
            {
                printf("\nDatabase saved successfully.\n");
            }
            else
            {
                printf("\nERROR: Database save failed.\n");
            }

            if (continue_or_exit() == FAILURE)
            {
                return SUCCESS;
            }
            break;

        case 6:
            printf("\nExiting program...\n");

            return SUCCESS;

        default:
            printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 6);

    return SUCCESS;
}