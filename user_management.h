#include <stdio.h>

typedef struct _User
{
	unsigned int id;	//user's ID
	char *name;			//user's name
	char *username;		//user's username
	char *password;		//user's password
	Bookid *array;		//book's id
	struct _User *next; //next
} User;

typedef struct _UserArray
{
	User *array;
	unsigned int length;
	struct _UserArray *next;
} UserArray;

typedef struct _bookid
{
	unsigned int length; //the number of borrowed book(must <3)
	unsigned int bookid1;
	unsigned int bookid2;
	unsigned int bookid3;
} Bookid;

int store_users(FILE *file, UserArray *puserarray);

int store_users(FILE *file, UserArray *puserarray);

int add_users(User *puser, UserArray *puserarray);

int remove_users(User *puser, UserArray *puserarray);

int borrow_book(Book *pbook, User *puser);

int return_book(Book *pbook, User *puser);