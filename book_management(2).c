#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_management(2).h"

int store_books(FILE *file)
{
    file=fopen("library.txt","wb");
    if(!file)
    {
        printf("Error!\n");
        exit(-1);
    }
    for(int i=0;i<1000;i++)
    {
        Book i;
        fwrite(i.authors,sizeof(i),1,file);
        fwrite(i.copies,sizeof(i),1,file);
        fwrite(i.id,sizeof(i),1,file);
        fwrite(i.next,sizeof(i),1,file);
        fwrite(i.title,sizeof(i),1,file);
        fwrite(i.year,sizeof(i),1,file);
    }
    fclose(file);
    return 0;
}

int load_books(FILE *file)
{
    file=fopen("library.txt","rb");
    if(!file)
    {
        printf("The wrong databases.\n");
        exit(-1);
    }
    for(int i=0;i<1000;i++)
    {
        Book i;
        fread(i.authors,sizeof(i),1,file);
        fread(i.copies,sizeof(i),1,file);
        fread(i.id,sizeof(i),1,file);
        fread(i.next,sizeof(i),1,file);
        fread(i.title,sizeof(i),1,file);
        fread(i.year,sizeof(i),1,file);
    }
    fclose(file);
    return 0;
}

int add_book(Book book)
{

}

int remove_book(Book book)
{
    

}
