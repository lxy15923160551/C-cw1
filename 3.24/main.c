#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_management(2).h"

int main()
{
    int option, year1, copies1, id;
    char *username, *password, *title, *author, *year, *copies;
    BookArray *pbookarray;
    UserArray *puserarray;
    UserArray head;
    username = (char *)malloc(100 * sizeof(char));
    password = (char *)malloc(100 * sizeof(char));
    title = (char *)malloc(100 * sizeof(char));
    author = (char *)malloc(100 * sizeof(char));
    year = (char *)malloc(100 * sizeof(char));
    copies = (char *)malloc(100 * sizeof(char));
    //
mainmenu:
    printmenu();
    scanf("%i", &option);
    while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5)
    {
        printf("Sorry, the option you entered was invalid, please try again.\n");
        printmenu();
        scanf("%i", &option);
    }
    if (option == 1)
    {
        printf("Please enter a username:");
        scanf("%s", username);
        printf("Please enter a password:");
        scanf("%s", password);
        while (checkusersame(username, puserarray) == 1 || strcmp(username, "librarian") == 0)
        {
            printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
            printf("Please enter a username:");
            scanf("%s", username);
            printf("Please enter a password:");
            scanf("%s", password);
        }
        User *a;
        a->id = 1;
        a->username = username;
        a->password = password;
        add_users(a, puserarray);
        printf("Registered library account successfully!\n");
        goto mainmenu;
    }

    else if (option == 2)
    {
        printf("Please enter your username:");
        scanf("%s", username);
        printf("Please enter your password:");
        scanf("%s", password);
        if (strcmp(username, "librarian") == 0 && strcmp(password, "librarian") == 0)
        {
        ba:
            limenu();
            scanf("%i", &option);
            while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5) //判斷是否有效
            {
                printf("Sorry, the option you entered was invalid, please try again.\n");
                printmenu();
                scanf("%i", &option);
            }
            printf("\n");
            if (option == 1)
            {
            baa:
                printf("Enter the title of the book you wish to add:");
                fflush(stdin);
                gets(title);
                printf("Enter the author of the book you wish to add:");
                fflush(stdin);
                gets(author);
                printf("Enter the year that the book you wish to add was released:");
                fflush(stdin);
                gets(year);
                printf("Enter the number of copies of the book that you wish to add:");
                gets(copies);
                if (strspn(year, "0123456789") != strlen(year) || strspn(copies, "0123456789") != strlen(copies))
                {
                    printf("Sorry, you attempted to add an invalid book, please try again.\n");
                    goto baa;
                }
                year1 = atoi(year);
                copies1 = atoi(copies);
                Book *a;
                a->title = title;
                a->authors = author;
                a->year = year1;
                a->copies = copies1;
                if (add_book(a, pbookarray) == 1)
                {
                    printf("This book has existed, please try again.");
                }
                printf("Book was successfully added!");
                goto ba;
            }
            if (option == 2)
            {
                /* code */
            }
            if (option == 3)
            {
                /* code */
            }
            if (option == 4)
            {
                /* code */
            }
            if (option == 5)
            {
                printf("Logging out...\n");
                goto mainmenu;
            }
        }
        if (checkusersame(username, puserarray) == 1 && checkpasssame(password, puserarray) == 1)
        {
        bb:
            usmenu(username);
            scanf("%i", &option);
            while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5) //判斷是否有效
            {
                printf("Sorry, the option you entered was invalid, please try again.\n");
                printmenu();
                scanf("%i", &option);
            }
            if (option == 1)
            {
                printf("Enter the ID number of the book you wish to borrow:");
                scanf("%i", id);
                while (pbookarray->array != NULL)
                {
                    if (pbookarray->array->id == id)
                    {
                        break;
                    }
                    pbookarray->array = pbookarray->array->next;
                }
                while (puserarray->array != NULL)
                {
                    if (puserarray->array->username == username)
                    {
                        break;
                    }
                    puserarray->array = puserarray->array->next;
                }
                if (pbookarray->array->id == id)
                {
                    if (borrow_book(pbookarray->array, puserarray->array) == 0)
                    {
                        printf("You have successfully borrowed the book!\n");
                        goto bb;
                    }
                }
                else
                {
                    printf("This book is not available here.\n");
                    goto bb;
                }
            }
            if (option == 2)
            {
                /* code */
            }
            if (option == 3)
            {
                /* code */
            }
            if (option == 4)
            {
                /* code */
            }
            if (option == 5)
            {
                printf("Logging out...\n");
                goto mainmenu;
            }
        }
    }

    else if (option == 3)
    {
        printf("Loading search menu...\n");
        c:
        semenu();
        scanf("%i", &option);
        while (option != 1 && option != 2 && option != 3 && option != 4)
        {
            printf("Sorry, the option you entered was invalid, please try again.\n");
            semenu;
            scanf("%i", &option);
        }
        if (option == 1)
        {
            printf("Please enter title:");
            gets(title);
            BookArray findbook = find_book_by_title();
            printf("ID    Title           Authors     Year  Copies\n");
            for (int i = 0; i < findbook.length; i++)
            {
                printf("%i%s%s%i%i", findbook.array->id, findbook.array->title, findbook.array->authors, findbook.array->year, findbook.array->copies);
                findbook = findbook.next;
            }
            goto c;
        }
        if (option == 2)
        {
            printf("Please enter author:");
            gets(author);
            BookArray findbook = find_book_by_title();
            printf("ID    Title           Authors     Year  Copies\n");
            for (int i = 0; i < findbook.length; i++)
            {
                printf("%i%s%s%i%i", findbook.array->id, findbook.array->title, findbook.array->authors, findbook.array->year, findbook.array->copies);
                findbook = findbook.next;
            }
            goto c;
        }
        if (option == 3)
        {
            printf("Please enter year:");
            gets(year);
            year1=year;
            BookArray findbook = find_book_by_title();
            printf("ID    Title           Authors     Year  Copies\n");
            for (int i = 0; i < findbook.length; i++)
            {
                printf("%i%s%s%i%i", findbook.array->id, findbook.array->title, findbook.array->authors, findbook.array->year, findbook.array->copies);
                findbook = findbook.next;
            }
            goto c;
        }
        if (option == 4)
        {
            printf("Loading main menu...\n");
            goto mainmenu;
        }
    }

    else if (option == 4)
    {
        /* code */
    }

    else
    {
        printf("Thank you for using the library!\n");
        printf("Goodbye!");
    }
    return 0;
}
