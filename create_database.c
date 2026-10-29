
#include "inverted_search.h"

// Function to create the inverted database
int create_database(hash_t *arr, int size, Dlist *head, Dlist *tail)
{
    // tail is not required in this function
    (void)tail;

    // Start from the first file in the doubly linked list
    Dlist *file_temp = head;

    // Process every file in the doubly linked list
    while (file_temp != NULL)
    {
        // Open the current file in read mode
        FILE *fp = fopen(file_temp->filename, "r");

        // Check whether the file was opened successfully
        if (fp == NULL)
        {
            printf("ERROR: Unable to open %s\n", file_temp->filename);

            // Move to the next file
            file_temp = file_temp->next;
            continue;
        }

        // Array to store one word read from the file
        char word[100];

        // Read the file one word at a time
        while (fscanf(fp, "%s", word) != EOF)
        {
            int index;

            // Calculate the hash index using the first character
            // Calculate the index of the word
            if (isalpha((unsigned char)word[0]))
            {
                index = word[0] % (size - 1);
            }
            else
            {
                index = size - 1;
            }

            // Start searching the main-node list of this bucket
            main_t *main_temp = arr[index].main_link;

            // Store the previous main node
            main_t *previous_main = NULL;

            // Search for the word in the main-node list
            while (main_temp != NULL)
            {
                // Compare the current word with the main-node word
                if (strcmp(main_temp->word, word) == 0)
                {
                    // Word found
                    break;
                }

                // Move previous_main to the current node
                previous_main = main_temp;

                // Move to the next main node
                main_temp = main_temp->main_link;
            }

            // If main_temp is NULL, the word was not found
            if (main_temp == NULL)
            {
                // Allocate memory for a new main node
                main_t *new_main = malloc(sizeof(main_t));

                // Allocate memory for a new sub node
                sub_t *new_sub = malloc(sizeof(sub_t));

                // Check whether memory allocation failed
                if (new_main == NULL || new_sub == NULL)
                {
                    printf("ERROR: Memory allocation failed\n");

                    // Free any successfully allocated memory
                    free(new_main);
                    free(new_sub);

                    // Close the file
                    fclose(fp);

                    return FAILURE;
                }

                // Store the word in the main node
                strcpy(new_main->word, word);

                // Initially, the word is present in one file
                new_main->file_count = 1;

                // The new main node is not connected to another main node yet
                new_main->main_link = NULL;

                // The word occurs once in the current file
                new_sub->word_count = 1;

                // Store the current filename in the sub node
                strcpy(new_sub->filename, file_temp->filename);

                // The new sub node is the last sub node
                new_sub->sub_link = NULL;

                // Connect the sub node to the main node
                new_main->sub_link = new_sub;

                // Insert the new main node into the hash bucket
                if (arr[index].main_link == NULL)
                {
                    // The bucket is empty, so insert the first main node
                    arr[index].main_link = new_main;
                }
                else
                {
                    // The bucket is not empty, so attach the node at the end
                    previous_main->main_link = new_main;
                }

                printf("Created main node for word: %s\n", word);
            }
            else
            {
                // The word already exists in the database

                // Start searching the sub-node list of this main node
                sub_t *sub_temp = main_temp->sub_link;

                // Store the previous sub node
                sub_t *previous_sub = NULL;

                // Search for the current filename
                while (sub_temp != NULL)
                {
                    // Compare the stored filename with the current filename
                    if (strcmp(sub_temp->filename, file_temp->filename) == 0)
                    {
                        // Filename found
                        break;
                    }

                    // Move previous_sub to the current sub node
                    previous_sub = sub_temp;

                    // Move to the next sub node
                    sub_temp = sub_temp->sub_link;
                }

                // Same word and same filename found
                if (sub_temp != NULL)
                {
                    // Increase the number of occurrences of the word
                    sub_temp->word_count++;

                    printf("Updated word count for: %s\n", word);
                }
                else
                {
                    // Same word but a different filename was found

                    // Allocate memory for a new sub node
                    sub_t *new_sub = malloc(sizeof(sub_t));

                    // Check whether memory allocation failed
                    if (new_sub == NULL)
                    {
                        printf("ERROR: Memory allocation failed\n");

                        // Close the file
                        fclose(fp);

                        return FAILURE;
                    }

                    // The word occurs once in the new file
                    new_sub->word_count = 1;

                    // Store the new filename
                    strcpy(new_sub->filename, file_temp->filename);

                    // The new sub node is the last node
                    new_sub->sub_link = NULL;

                    // Attach the new sub node after the previous sub node
                    previous_sub->sub_link = new_sub;

                    // Increase the number of files containing this word
                    main_temp->file_count++;

                    printf("Added new file for word: %s\n", word);
                }
            }
        }

        // Close the current file
        fclose(fp);

        // Move to the next file in the doubly linked list
        file_temp = file_temp->next;
    }

    // Database creation completed successfully
    return SUCCESS;
}