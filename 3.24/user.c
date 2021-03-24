#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_management(2).h"

int store_users(FILE *file, UserArray *puserarray)
{
    if (!file) //wrong file
    {
        printf("Error!\n");
        exit(-1);
    }
    fwrite(&(puserarray->length), sizeof(unsigned int), 1, file);
    User *pu = puserarray->array;
    while (pu != NULL) //no users
    {
        fwrite(pu->name, 100 * sizeof(char), 1, file);
        fwrite(pu->username, 100 * sizeof(char), 1, file);
        fwrite(pu->password, 100 * sizeof(char), 1, file);
        fwrite(&(pu->id), sizeof(unsigned int), 1, file);
        fwrite(pu->array), sizeof(unsigned int), 1, file);
        pu = pu->next;
    }
    return 0;
}

int load_users(FILE *file, UserArray *puserarray)
{
    if (!file) //wrong file
    {
        printf("The wrong databases.\n");
        exit(-1);
    }
    fread(&(puserarray->length), sizeof(unsigned int), 1, file);
    puserarray->array = NULL;
    User *pu = puserarray->array;
    for (int i = 0; i < puserarray->length; i++) //read users until there is no book
    {
        pu = (User *)malloc(sizeof(User)); //give memory
        pu->name = (char *)malloc(100 * sizeof(char));
        pu->username = (char *)malloc(100 * sizeof(char));
        pu->password = (char *)malloc(100 * sizeof(char));
        memset(pu->name, 0, sizeof(char) * 100); //delete
        memset(pu->username, 0, sizeof(char) * 100);
        memset(pu->password, 0, sizeof(char) * 100);

        fread(pu->name, 100 * sizeof(char), 1, file);
        fread(pu->username, 100 * sizeof(char), 1, file);
        fread(pu->password, 100 * sizeof(char), 1, file);
        fread(&(pu->id), sizeof(unsigned int), 1, file);
        fread(&(pu->array), sizeof(unsigned int), 1, file);
        pu = pu->next;
    }

    return 0;
}

int add_users(User *puser, UserArray *puserarray)
{
    User *up;
    up = puserarray->array;
    for (int i = 0; i < puserarray->length; i++)
    {
        if (strcmp(puser->id, puserarray->array->id) == 0)
        {
            return 1;
        }
        up = up->next;
    }

    User *pu;
    pu = puserarray->array;
    if (pu == NULL)
    {
        puser->id = 1;
        puserarray->array = puser;
        puserarray->length++;
        return 0;
    }
    while (pu->next != NULL)
    {
        pu = pu->next;
    }
    puser->id = pu->id + 1;
    pu->next = puser;
    puserarray->length++;
    return 0;
}

int remove_users(User *puser, UserArray *puserarray)
{
    User *pu;
    pu = puserarray->array;
    for (int i = 0; i < puserarray->length; i++)
    {
        if (strcmp(puser->id, pu->id) == 0)
        {
            pu = NULL;
            return 0;
        }
        return 1;
    }
}

int borrow_book(Book *pbook, User *puser) //return 1 失敗;return 0 成功
{
    if (pbook->id==puser->array->bookid1||pbook->id==puser->array->bookid2||pbook->id==puser->array->bookid3)
    {
        printf("Sorry, you already have a copy of this book on loan.\n");
        return 1;
    }
    if (pbook->copies == 0)
    {
        printf("There is no this book.");
        return 1;
    }
    if (puser->array->length == 3)
    {
        printf("You can not borrow books before you return the book you borrowed.");
        return 1;
    }
    if (puser->array->length == 0)
    {
        pbook->copies--;
        puser->array->bookid1 = pbook->id;
        puser->array->length++;
        return 0;
    }
    if (puser->array->length == 1)
    {
        pbook->copies--;
        puser->array->bookid2 = pbook->id;
        puser->array->length++;
        return 0;
    }
    if (puser->array->length == 2)
    {
        pbook->copies--;
        puser->array->bookid3 = pbook->id;
        puser->array->length++;
        return 0;
    }
}

int return_book(Book *pbook, User *puser)
{
    if (pbook->id == puser->array->bookid3)
    {
        pbook->copies++;
        puser->array->bookid3 = 0;
        puser->array->length--;
        return 0;
    }
    if (pbook->id == puser->array->bookid2)
    {
        pbook->copies++;
        puser->array->bookid2 = 0;
        puser->array->length--;
        return 0;
    }
    if (pbook->id == puser->array->bookid1)
    {
        pbook->copies++;
        puser->array->bookid1 = 0;
        puser->array->length--;
        return 0;
    }
}
