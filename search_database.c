#include "inverted_search.h"

// Function to search a word in the inverted database
int search_database(hash_t *arr)
{
    char word[100];
    int index;
    int total_word_count = 0;

    main_t *temp;
    sub_t *sub_temp;

    printf("\nEnter the word to search: ");
    scanf("%s", word);

    // Check whether the first character is an alphabet
    if (isalpha((unsigned char)word[0]))
    {
        // Calculate index using the same formula as create_database.c
        index = word[0] % (SIZE - 1);
    }
    else
    {
        // Non-alphabetical words go to index 26
        index = SIZE - 1;
    }

    // Check whether the bucket contains main nodes
    if (arr[index].main_link != NULL)
    {
        temp = arr[index].main_link;

        // Traverse the main-node list
        while (temp != NULL)
        {
            if (strcmp(temp->word, word) == 0)
            {
                sub_temp = temp->sub_link;

                // Calculate total word count
                while (sub_temp != NULL)
                {
                    total_word_count += sub_temp->word_count;
                    sub_temp = sub_temp->sub_link;
                }

                printf("\nSearch Result:\n");

                printf("Index      : %d\n", index);
                printf("Word       : %s\n", temp->word);
                printf("File Count : %d\n", temp->file_count);
                printf("Word Count : %d\n", total_word_count);

                printf("File Names : ");

                // Display all file names
                sub_temp = temp->sub_link;

                while (sub_temp != NULL)
                {
                    printf("%s", sub_temp->filename);

                    if (sub_temp->sub_link != NULL)
                    {
                        printf(", ");
                    }

                    sub_temp = sub_temp->sub_link;
                }

                printf("\n");

                return SUCCESS;
            }

            temp = temp->main_link;
        }
    }

    printf("\nERROR: Word '%s' not found in the database.\n", word);

    return FAILURE;
}