#include "inverted_search.h"

// Function to save the inverted database
int save_database(hash_t *hash_table)
{
    char filename[100];
    char *extension;
    int choice;
    int i;
    main_t *main_temp;
    sub_t *sub_temp;
    FILE *fp;

    printf("\nEnter the backup file name: ");
    if (scanf("%99s", filename) != 1)
    {
        printf("ERROR: Invalid filename.\n");
        return FAILURE;
    }

    // Check file extension
    extension = strrchr(filename, '.');

    if (extension == NULL || strcmp(extension, ".txt") != 0)
    {
        printf("ERROR: Please enter a .txt file.\n");
        return FAILURE;
    }

    // Check whether file already exists
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        // File does not exist, create new file
        fp = fopen(filename, "w");

        if (fp == NULL)
        {
            printf("ERROR: Cannot create file.\n");
            return FAILURE;
        }

        // Write database into the new file
        for (i = 0; i < SIZE; i++)
        {
            main_temp = hash_table[i].main_link;

            while (main_temp != NULL)
            {
                fprintf(fp, "#%d : %s : %d : ",
                        i,
                        main_temp->word,
                        main_temp->file_count);

                // Write each filename and its word count
                sub_temp = main_temp->sub_link;

                while (sub_temp != NULL)
                {
                    fprintf(fp, "%s : %d",
                            sub_temp->filename,
                            sub_temp->word_count);

                    if (sub_temp->sub_link != NULL)
                    {
                        fprintf(fp, " : ");
                    }

                    sub_temp = sub_temp->sub_link;
                }

                fprintf(fp, " #\n");
                main_temp = main_temp->main_link;
            }
        }

        fclose(fp);
        printf("\nDatabase saved successfully.\n");
        return SUCCESS;
    }

    // File already exists
    fseek(fp, 0, SEEK_END);

    // Check whether file is empty
    if (ftell(fp) == 0)
    {
        fclose(fp);

        fp = fopen(filename, "w");

        if (fp == NULL)
        {
            printf("ERROR: Cannot open file.\n");
            return FAILURE;
        }

        // Write database into empty file
        for (i = 0; i < SIZE; i++)
        {
            main_temp = hash_table[i].main_link;

            while (main_temp != NULL)
            {
                fprintf(fp, "#%d : %s : %d : ",
                        i,
                        main_temp->word,
                        main_temp->file_count);

                sub_temp = main_temp->sub_link;

                while (sub_temp != NULL)
                {
                    fprintf(fp, "%s : %d",
                            sub_temp->filename,
                            sub_temp->word_count);

                    if (sub_temp->sub_link != NULL)
                    {
                        fprintf(fp, " : ");
                    }

                    sub_temp = sub_temp->sub_link;
                }

                fprintf(fp, " #\n");
                main_temp = main_temp->main_link;
            }
        }

        fclose(fp);
        printf("\nDatabase saved successfully.\n");
        return SUCCESS;
    }

    // File is not empty
    rewind(fp);

    // Check first character
    if (fgetc(fp) != '#')
    {
        printf("ERROR: Invalid backup file.\n");
        fclose(fp);
        return FAILURE;
    }

    fclose(fp);

    printf("\nBackup file already contains data.\n");
    printf("1. Overwrite\n");
    printf("2. Append\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1)
    {
        printf("ERROR: Invalid choice.\n");
        return FAILURE;
    }

    if (choice == 1)
    {
        fp = fopen(filename, "w");

        if (fp == NULL)
        {
            printf("ERROR: Cannot open file.\n");
            return FAILURE;
        }

        // Overwrite old database
        for (i = 0; i < SIZE; i++)
        {
            main_temp = hash_table[i].main_link;

            while (main_temp != NULL)
            {
                fprintf(fp, "#%d : %s : %d : ",
                        i,
                        main_temp->word,
                        main_temp->file_count);

                sub_temp = main_temp->sub_link;

                while (sub_temp != NULL)
                {
                    fprintf(fp, "%s : %d",
                            sub_temp->filename,
                            sub_temp->word_count);

                    if (sub_temp->sub_link != NULL)
                    {
                        fprintf(fp, " : ");
                    }

                    sub_temp = sub_temp->sub_link;
                }

                fprintf(fp, " #\n");
                main_temp = main_temp->main_link;
            }
        }

        fclose(fp);
        printf("\nDatabase overwritten successfully.\n");
    }
    else if (choice == 2)
    {
        fp = fopen(filename, "a");

        if (fp == NULL)
        {
            printf("ERROR: Cannot open file.\n");
            return FAILURE;
        }

        // Append database at the end
        for (i = 0; i < SIZE; i++)
        {
            main_temp = hash_table[i].main_link;

            while (main_temp != NULL)
            {
                fprintf(fp, "#%d : %s : %d : ",
                        i,
                        main_temp->word,
                        main_temp->file_count);

                sub_temp = main_temp->sub_link;

                while (sub_temp != NULL)
                {
                    fprintf(fp, "%s : %d",
                            sub_temp->filename,
                            sub_temp->word_count);

                    if (sub_temp->sub_link != NULL)
                    {
                        fprintf(fp, " : ");
                    }

                    sub_temp = sub_temp->sub_link;
                }

                fprintf(fp, " #\n");
                main_temp = main_temp->main_link;
            }
        }

        fclose(fp);
        printf("\nDatabase appended successfully.\n");
    }
    else
    {
        printf("\nERROR: Invalid choice.\n");
        return FAILURE;
    }

    return SUCCESS;
}
