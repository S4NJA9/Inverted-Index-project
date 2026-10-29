#include "inverted_search.h"

// Function to validate and store input files
int file_handling(Dlist **head, Dlist **tail, char *argv[])
{
    int i = 1;
    int duplicate;

    Dlist *new_node;
    Dlist *temp;

    char *extension;
    FILE *fp;

    // Process every command-line argument
    while (argv[i] != NULL)
    {
        // Find the last dot in the filename
        extension = strrchr(argv[i], '.');

        // Check whether the file has an extension
        if (extension == NULL)
        {
            printf("ERROR: %s has no file extension.\n", argv[i]);
            i++;
            continue;
        }

        // Accept only .txt files
        if (strcmp(extension, ".txt") == 0)
        {
            printf("Accepted file: %s\n", argv[i]);

            // Open the file
            fp = fopen(argv[i], "r");

            // Check whether the file exists
            if (fp == NULL)
            {
                printf("ERROR: Cannot open file: %s\n", argv[i]);
                i++;
                continue;
            }

            // Move to the end of the file
            fseek(fp, 0, SEEK_END);

            // Check whether the file is empty
            if (ftell(fp) == 0)
            {
                printf("ERROR: File is empty: %s\n", argv[i]);

                fclose(fp);
                i++;
                continue;
            }

            // Move back to the beginning of the file
            rewind(fp);

            // Initially, assume the file is not a duplicate
            duplicate = 0;

            // Start checking from the first list node
            temp = *head;

            // Check whether the file already exists
            while (temp != NULL)
            {
                if (strcmp(temp->filename, argv[i]) == 0)
                {
                    duplicate = 1;
                    break;
                }

                temp = temp->next;
            }

            // Reject duplicate files
            if (duplicate == 1)
            {
                printf("ERROR: Duplicate file: %s\n", argv[i]);

                fclose(fp);
                i++;
                continue;
            }

            // Allocate memory for a new node
            new_node = malloc(sizeof(Dlist));

            if (new_node == NULL)
            {
                printf("ERROR: Memory allocation failed.\n");

                fclose(fp);
                i++;
                continue;
            }

            // Copy the filename into the new node
            strcpy(new_node->filename, argv[i]);

            // Initialize the links
            new_node->prev = NULL;
            new_node->next = NULL;

            // Insert the first node
            if (*head == NULL && *tail == NULL)
            {
                *head = new_node;
                *tail = new_node;
            }
            else
            {
                // Insert the node at the end of the list
                new_node->prev = *tail;
                (*tail)->next = new_node;
                *tail = new_node;
            }

            printf("File inserted successfully: %s\n", argv[i]);

            // Close the file
            fclose(fp);
        }
        else if (strcmp(extension, ".c") == 0 ||
                 strcmp(extension, ".sh") == 0)
        {
            // Ignore C and shell script files
            printf("Ignored file: %s\n", argv[i]);
        }
        else
        {
            // Reject unsupported file extensions
            printf("ERROR: Unsupported file: %s\n", argv[i]);
        }

        // Move to the next command-line argument
        i++;
    }

    return SUCCESS;
}