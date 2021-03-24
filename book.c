#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_management(2).h"

int store_books(FILE *file, BookArray *pbookarray) //
{
    if (!file) //wrong file
    {
        printf("Error!\n");
        exit(-1);
    }
    fwrite(&(pbookarray->length), sizeof(unsigned int), 1, file);
    Book *pb = pbookarray->array;
    while (pb != NULL) //no books
    {
        fwrite(pb->authors, 100 * sizeof(char), 1, file);
        fwrite(&(pb->copies), sizeof(unsigned int), 1, file);
        fwrite(&(pb->id), sizeof(unsigned int), 1, file);
        fwrite(pb->title, 100 * sizeof(char), 1, file);
        fwrite(&(pb->year), sizeof(unsigned int), 1, file);
        pb = pb->next;
    }
    return 0;
}

int load_books(FILE *file, BookArray *pbookarray)
{
    if (!file) //wrong file
    {
        printf("The wrong databases.\n");
        exit(-1);
    }
    fread(&(pbookarray->length), sizeof(unsigned int), 1, file);
    pbookarray->array = NULL;
    Book *pb = pbookarray->array;
    for (int i = 0; i < pbookarray->length; i++) //read books until there is no book
    {
        pb = (Book *)malloc(sizeof(Book)); //give memory
        pb->title = (char *)malloc(100 * sizeof(char));
        pb->authors = (char *)malloc(100 * sizeof(char));
        memset(pb->title, 0, sizeof(char) * 100); //delete
        memset(pb->authors, 0, sizeof(char) * 100);

        fread(pb->authors, 100 * sizeof(char), 1, file);
        fread(&(pb->copies), sizeof(unsigned int), 1, file);
        fread(&(pb->id), sizeof(unsigned int), 1, file);
        fread(pb->title, 100 * sizeof(char), 1, file);
        fread(&(pb->year), sizeof(unsigned int), 1, file);
        pb = pb->next;
    }

    return 0;
}

int add_book(Book *pbook, BookArray *pbookarray)
{
    Book *bp;
    bp = pbookarray->array;
    for (int i = 0; i < pbookarray->length; i++) //check if the book existed or not
    {
        if (strcmp(pbook->id, pbookarray->array->id) == 0) //exist the same book
        {
            return 1;
        }
        bp = bp->next;
    }

    Book *pb;
    pb = pbookarray->array;
    if (pb == NULL) //no books in bookarray
    {
        pbook->id = 1;
        pbookarray->array = pbook;
        pbookarray->length++;
        return 0;
    }

    while (pb->next != NULL) //find the last book
    {
        pb = pb->next;
    }
    pbook->id = pb->id + 1;
    pb->next = pbook;
    pbookarray->length++;
    return 0;
}

int remove_book(Book *pbook, BookArray *pbookarray)
{
    Book *bp;
    bp = pbookarray->array;
    for (int i = 0; i < pbookarray->length; i++)
    {
        if (strcmp(pbook->id, bp->id) == 0) //check if there is the same book
        {
            bp = NULL;
            return 0;
        }
        bp = bp->next;
    }
    return 1; // if there is no this book
}

BookArray find_book_by_title(const char *title, BookArray *pbookarray)
{
    BookArray findbook;
    findbook.length = 0;
    for (int i = 0; i < pbookarray->length; i++)
    {
        if (strstr(pbookarray->array->title, title) != NULL) //have the same string
        {
            findbook.length++;
            findbook.array = pbookarray->array;
            findbook.array = findbook.array->nextfind;
        }
        pbookarray = pbookarray->next;
    }
    return findbook;
}

BookArray find_book_by_author(const char *author, BookArray *pbookarray)
{
    BookArray findbook;
    findbook.length = 0;
    for (int i = 0; i < pbookarray->length; i++)
    {
        if (strstr(pbookarray->array->authors, author) != NULL) //have the same string
        {
            findbook.length++;
            findbook.array = pbookarray->array;
            findbook.array = findbook.array->nextfind;
        }
        pbookarray = pbookarray->next;
    }
    return findbook;
}

BookArray find_book_by_year(unsigned int year, BookArray *pbookarray)
{
    BookArray findbook;
    findbook.length = 0;
    for (int i = 0; i < pbookarray->length; i++)
    {
        if (pbookarray->array->year == year)
        {
            findbook.length++;
            findbook.array = pbookarray->array;
            findbook.array = findbook.array->nextfind;
        }
        pbookarray = pbookarray->next;
    }
    return findbook;
}