
#ifndef BOOK_MANAGEMENT_GUARD__H
#define BOOK_MANAGEMENT_GUARD__H

#include <stdio.h>

/*You can extend the structs (Book and BookArray) defined in this head file;
  However, you may not change the function prototypes. 
  You are also free to add additional head files and data structures as needed. 
*/

typedef struct _Book
{
	unsigned int id;		//Book ID
	char *title;			//book title
	char *authors;			//comma separated list of authors
	unsigned int year;		// year of publication
	unsigned int copies;	//number of copies the library has
	struct _Book *next;		//next
	struct _Book *nextfind; //find the next book
} Book;

typedef struct _BookArray
{
	Book *array;			 // pointer to array (or linked list) of struct Book.
	unsigned int length;	 // number of elements in the (Book*) array
	struct _BookArray *next; //next
} BookArray;

typedef struct _bookid
{
	unsigned int length; //the number of borrowed book(must <3)
	unsigned int bookid1;
	unsigned int bookid2;
	unsigned int bookid3;
} Bookid;

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

//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(FILE *file, BookArray *pbookarray);

//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
int load_books(FILE *file, BookArray *pbookarray);

//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book *pbook, BookArray *pbookarray);

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book *pbook, BookArray *pbookarray);

//finds books with a given title.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_title(const char *title, BookArray *pbookarray);

//finds books with the given authors.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_author(const char *author, BookArray *pbookarray);

//finds books published in the given year.
//returns a BookArray structure, where the field "array" is a newly allocated array of books, or null if no book with the
//provided title can be found. The length of the array is also recorded in the returned structure, with 0 in case
//array is the null pointer.
BookArray find_book_by_year(unsigned int year, BookArray *pbookarray);

int store_users(FILE *file, UserArray *puserarray);

int load_users(FILE *file, UserArray *puserarray);

int add_users(User *puser, UserArray *puserarray);

int remove_users(User *puser, UserArray *puserarray);

int borrow_book(Book *pbook, User *puser);

int return_book(Book *pbook, User *puser);

//menu
void printmenu();

int checkusersame(const char *check, UserArray *puserarray);

int checkpasssame(const char *check, UserArray *puserarray);

void limenu();

void semenu();

void usmenu(const char *username);
#endif
