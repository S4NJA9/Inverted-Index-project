#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inverted_search.h"

int update_database(hash_t *hash_table)
{
    char filename[100];
    char word[100];
    char sub_filename[100];
    char delimiter;
    char *extension;

    int index;
    int file_count;
    int word_count;
    int i;

    FILE *fp;

    printf("Enter backup file name: ");
    if (scanf("%99s", filename) != 1)
    {
        printf("Error: Invalid filename input\n");
        return FAILURE;
    }

    /* Validate .txt extension */
    extension = strrchr(filename, '.');

    if (extension == NULL || strcmp(extension, ".txt") != 0)
    {
        printf("Error: Backup file must have .txt extension\n");
        return FAILURE;
    }

    /* Open backup file */
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: Unable to open backup file\n");
        return FAILURE;
    }

    /* Validate first character */
    if (fgetc(fp) != '#')
    {
        printf("Error: Invalid backup file format\n");
        fclose(fp);
        return FAILURE;
    }

    rewind(fp);

    while (1)
    {
        /*
         * Read:
         * #18 : hello : 2
         */
        int result = fscanf(fp, " #%d : %99s : %d",
                            &index, word, &file_count);

        if (result == EOF)
            break;

        if (result != 3 || index < 0 || index >= SIZE ||
            file_count <= 0)
        {
            printf("Error: Invalid record in backup file\n");
            fclose(fp);
            return FAILURE;
        }

        /* Prevent duplicate words in the hash table */
        main_t *existing = hash_table[index].main_link;

        while (existing != NULL)
        {
            if (strcmp(existing->word, word) == 0)
            {
                printf("Error: Word '%s' already exists in database\n",
                       word);
                fclose(fp);
                return FAILURE;
            }

            existing = existing->main_link;
        }

        /* Create main node */
        main_t *main_node = malloc(sizeof(main_t));

        if (main_node == NULL)
        {
            printf("Error: Memory allocation failed\n");
            fclose(fp);
            return FAILURE;
        }

        strcpy(main_node->word, word);
        main_node->file_count = file_count;
        main_node->sub_link = NULL;
        main_node->main_link = NULL;

        sub_t *last_sub = NULL;

        /* Read filename and word count for each file */
        for (i = 0; i < file_count; i++)
        {
            if (fscanf(fp, " : %99s : %d",
                       sub_filename, &word_count) != 2 ||
                word_count <= 0)
            {
                printf("Error: Invalid file information\n");

                sub_t *temp = main_node->sub_link;

                while (temp != NULL)
                {
                    sub_t *next = temp->sub_link;
                    free(temp);
                    temp = next;
                }

                free(main_node);
                fclose(fp);
                return FAILURE;
            }

            sub_t *sub_node = malloc(sizeof(sub_t));

            if (sub_node == NULL)
            {
                printf("Error: Memory allocation failed\n");

                sub_t *temp = main_node->sub_link;

                while (temp != NULL)
                {
                    sub_t *next = temp->sub_link;
                    free(temp);
                    temp = next;
                }

                free(main_node);
                fclose(fp);
                return FAILURE;
            }

            strcpy(sub_node->filename, sub_filename);
            sub_node->word_count = word_count;
            sub_node->sub_link = NULL;

            if (main_node->sub_link == NULL)
            {
                main_node->sub_link = sub_node;
            }
            else
            {
                last_sub->sub_link = sub_node;
            }

            last_sub = sub_node;
        }

        /* Validate record-ending # */
        if (fscanf(fp, " %c", &delimiter) != 1 ||
            delimiter != '#')
        {
            printf("Error: Missing record-ending #\n");

            sub_t *temp = main_node->sub_link;

            while (temp != NULL)
            {
                sub_t *next = temp->sub_link;
                free(temp);
                temp = next;
            }

            free(main_node);
            fclose(fp);
            return FAILURE;
        }

        /* Insert main node into its saved hash-table index */
        if (hash_table[index].main_link == NULL)
        {
            hash_table[index].main_link = main_node;
        }
        else
        {
            main_t *temp = hash_table[index].main_link;

            while (temp->main_link != NULL)
                temp = temp->main_link;

            temp->main_link = main_node;
        }
    }

    fclose(fp);
    return SUCCESS;
}

