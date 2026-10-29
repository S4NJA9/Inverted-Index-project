#include "inverted_search.h"

// Function to display the inverted database
void display_database(hash_t *hash_table)
{
    int i;
    int found = 0;
    int total_word_count;

    main_t *main_temp;
    sub_t *sub_temp;

    printf("\nInverted Database:\n");

    printf("%-5s : %-10s : %-10s : %-11s : %-30s \n",
           "Index",
           "Word",
           "File Count",
           "Word Count",
           "File Names");

    for (i = 0; i < SIZE; i++)
    {
        main_temp = hash_table[i].main_link;

        while (main_temp != NULL)
        {
            found = 1;
            total_word_count = 0;

            // Calculate total word count
            sub_temp = main_temp->sub_link;

            while (sub_temp != NULL)
            {
                total_word_count += sub_temp->word_count;
                sub_temp = sub_temp->sub_link;
            }

            printf("# %-5d : %-10s : %-10d : %-11d : ",
                   i,
                   main_temp->word,
                   main_temp->file_count,
                   total_word_count);

            // Display all filenames
            sub_temp = main_temp->sub_link;

            while (sub_temp != NULL)
            {
                printf("%s", sub_temp->filename);

                if (sub_temp->sub_link != NULL)
                {
                    printf(", ");
                }

                sub_temp = sub_temp->sub_link;
            }

            printf(" #\n");

            main_temp = main_temp->main_link;
        }
    }

    if (found == 0)
    {
        printf("Database is empty. Please create the database first.\n");
    }
}

// Function to display the menu
void print_menu(void)
{
    printf("\n");
    printf("1. Create database\n");
    printf("2. Display database\n");
    printf("3. Update database\n");
    printf("4. Search database\n");
    printf("5. Save database\n");
    printf("6. Exit\n");

    printf("Enter your choice: ");
}