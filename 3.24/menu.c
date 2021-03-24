#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_management(2).h"

void printmenu()
{
    printf("Please choose an option:\n");
    printf("1)Register anaccount\n");
    printf("2)Login\n");
    printf("3)Search for books\n");
    printf("4)Display all books\n");
    printf("5)Quit\n");
    printf(" Option:");
}

int checkusersame(const char *check, UserArray *puserarray) //檢查是否有相同用戶名 return 0 沒有相同；return 1 有相同
{
    User *pu = puserarray->array;
    for (int i = 0; i < puserarray->length; i++)
    {
        if (strcmp(check, pu->username) == 0)
        {
            return 1; //相同
        }
        pu = pu->next;
    }
    return 0; //不同
}

int checkpasssame(const char *check, UserArray *puserarray)
{
    User *pu = puserarray->array;
    for (int i = 0; i < puserarray->length; i++)
    {
        if (strcmp(check, pu->password) == 0)
        {
            return 1; //相同
        }
        pu = pu->next;
    }
    return 0; //不同
}

void limenu() //圖書管理員菜單
{
    printf("\n");
    printf("(logged in as: librarian)\n");
    printf("Please choose an option:\n");
    printf("1)Add a book\n");
    printf("2)Remove a book\n");
    printf("3)search for books\n");
    printf("4)Display all books\n");
    printf("5)log out\n");
    printf(" Option:");
}

void semenu() //搜索菜單
{
    printf("\n");
    printf("Please choose an option:\n");
    printf("1)Find books by title\n");
    printf("2)Find books by author\n");
    printf("3)Find books by year\n");
    printf("4)Return to previous menu\n");
    printf(" Option:");
}

void usmenu(const char *username)//用戶菜單
{
    printf("(Logged in as: %s)\n",username);
    printf("1)Borrow a book\n");
    printf("2)Return a book\n");
    printf("3)Search for books\n");
    printf("4)Display all books\n");
    printf("5)Log out\n");
    printf(" Option:");
}