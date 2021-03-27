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
        fwrite(&(pb->state), sizeof(unsigned int), 1, file);
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
    pb = (Book *)malloc(sizeof(Book));           //give memory
    for (int i = 0; i < pbookarray->length; i++) //read books until there is no book
    {
        pb->next = (Book *)malloc(sizeof(Book)); //give memory
        pb->title = (char *)malloc(100 * sizeof(char));
        pb->authors = (char *)malloc(100 * sizeof(char));
        memset(pb->title, 0, sizeof(char) * 100); //delete
        memset(pb->authors, 0, sizeof(char) * 100);

        fread(pb->authors, 100 * sizeof(char), 1, file);
        fread(&(pb->copies), sizeof(unsigned int), 1, file);
        fread(&(pb->id), sizeof(unsigned int), 1, file);
        fread(pb->title, 100 * sizeof(char), 1, file);
        fread(&(pb->year), sizeof(unsigned int), 1, file);
        fread(&(pb->state), sizeof(unsigned int), 1, file);
        pb = pb->next;
    }
    return 0;
}

int add_book(Book *pbook, BookArray *pbookarray)
{
    Book *pb;
    pb = pbookarray->array;
    if (pbookarray->length == 0) //no books in bookarray
    {
        pbook->id = 1;
        pbookarray->array = pbook;
        pbookarray->length++;
        return 0;
    }

    Book *bp;
    bp = pbookarray->array;
    for (int i = 0; i < pbookarray->length; i++) //check if the book existed or not
    {
        if (strcmp(pbook->title, pbookarray->array->title) == 0) //exist the same book
        {
            return 1;
        }
        bp = bp->next;
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

int remove_book(unsigned int id, BookArray *pbookarray)
{
    Book *pb;
    pb = pbookarray->array;
    for (int i = 0; i < pbookarray->length; i++)
    {
        if (id == pb->id && pb->next == 0) //check if there is the same book
        {
            memset(pbookarray->array, 0, sizeof(Book));
            pbookarray->length--;
            return 0; //return 0 成功删除
        }
        pb = pb->next;
    }
    return 1; // if there is no this book
}

void find_book_by_title(const char *title, BookArray *pbookarray, BookArray *pfindbook)
{
    Book *pb;
    pb = pbookarray->array;
    Book *pbb = pfindbook->array;
    for (int i = 0; i < pbookarray->length; i++)
    {
        if (strcmp(pb->title, title) == 0) //have the same string
        {
            if (pfindbook->length == 0)
            {
                pfindbook->array = pb;
                pfindbook->length++;
                pbb = pfindbook->array;
                pbb->nextfind = NULL;
            }
            else
            {
                pbb->nextfind = pb;
                pfindbook->length++;
                pbb = pbb->nextfind;
                pbb->nextfind = NULL;
            }
        }
        pb = pb->next;
    }
    if (pfindbook->length == 0) //沒有相關書籍
    {
        printf("No related books\n");
    }
    printf("ID    Title           Authors     Year  Copies\n");
    for (int i = 0; i < pfindbook->length; i++)
    {
        printf("%i%s%s%i%i\n", pbb->id, pbb->title, pbb->authors, pbb->year, pbb->copies);
        pbb = pbb->nextfind;
    }
}

void find_book_by_author(const char *author, BookArray *pbookarray, BookArray *pfindbook)
{
    Book *pb;
    pb = pbookarray->array;
    Book *pbb = pfindbook->array;
    for (int i = 0; i < pbookarray->length; i++)
    {
        if (strcmp(pb->authors, author) == 0) //have the same string
        {
            if (pfindbook->length == 0)
            {
                pfindbook->array = pb;
                pfindbook->length++;
                pbb = pfindbook->array;
                pbb->nextfind = NULL;
            }
            else
            {
                pbb->nextfind = pb;
                pfindbook->length++;
                pbb = pbb->nextfind;
                pbb->nextfind = NULL;
            }
        }
        pb = pb->next;
    }
    if (pfindbook->length == 0) //沒有相關書籍
    {
        printf("No related books\n");
    }
    printf("ID    Title           Authors     Year  Copies\n");
    for (int i = 0; i < pfindbook->length; i++)
    {
        printf("%i%s%s%i%i\n", pbb->id, pbb->title, pbb->authors, pbb->year, pbb->copies);
        pbb = pbb->nextfind;
    }
}

void find_book_by_year(unsigned int year, BookArray *pbookarray, BookArray *pfindbook)
{
    Book *pb;
    pb = pbookarray->array;
    Book *pbb = pfindbook->array;
    for (int i = 0; i < pbookarray->length; i++)
    {
        if (pb->year == year) //have the same string
        {
            if (pfindbook->length == 0)
            {
                pfindbook->array = pb;
                pfindbook->length++;
                pbb = pfindbook->array;
                pbb->nextfind = NULL;
            }
            else
            {
                pbb->nextfind = pb;
                pfindbook->length++;
                pbb = pbb->nextfind;
                pbb->nextfind = NULL;
            }
        }
        pb = pb->next;
    }
    if (pfindbook->length == 0) //沒有相關書籍
    {
        printf("No related books\n");
    }
    printf("ID    Title           Authors     Year  Copies\n");
    for (int i = 0; i < pfindbook->length; i++)
    {
        printf("%i%s%s%i%i\n", pbb->id, pbb->title, pbb->authors, pbb->year, pbb->copies);
        pbb = pbb->nextfind;
    }
}

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
        fwrite(pu->username, 100 * sizeof(char), 1, file);
        fwrite(pu->password, 100 * sizeof(char), 1, file);
        fwrite(&(pu->length), sizeof(unsigned int), 1, file);
        fwrite(&(pu->bookid1), sizeof(unsigned int), 1, file);
        fwrite(&(pu->bookid2), sizeof(unsigned int), 1, file);
        fwrite(&(pu->bookid3), sizeof(unsigned int), 1, file);
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
    pu = (User *)malloc(sizeof(User));           //give memory
    for (int i = 0; i < puserarray->length; i++) //read users until there is no book
    {
        pu->next = (User *)malloc(sizeof(User)); //give memory
        pu->username = (char *)malloc(100 * sizeof(char));
        pu->password = (char *)malloc(100 * sizeof(char));
        memset(pu->username, 0, sizeof(char) * 100);
        memset(pu->password, 0, sizeof(char) * 100);

        fread(pu->username, 100 * sizeof(char), 1, file);
        fread(pu->password, 100 * sizeof(char), 1, file);
        fread(&(pu->length), sizeof(unsigned int), 1, file);
        fread(&(pu->bookid1), sizeof(unsigned int), 1, file);
        fread(&(pu->bookid2), sizeof(unsigned int), 1, file);
        fread(&(pu->bookid3), sizeof(unsigned int), 1, file);
        pu = pu->next;
    }

    return 0;
}

int add_users(User *puser, UserArray *puserarray)
{
    User *pu;
    pu = puserarray->array;
    if (puserarray->length == 0)
    {
        puserarray->array = puser;
        puserarray->length++;
        return 0;
    }
    while (pu->next != NULL)
    {
        pu = pu->next;
    }
    pu->next = puser;
    puserarray->length++;
    return 0;
}

int borrow_book(Book *pbook, User *puser, BookArray *pborrowbook) //return 1 失敗;return 0 成功
{
    Book *pb;
    pb = pborrowbook->array;
    if (pbook->id == puser->bookid1 || pbook->id == puser->bookid2 || pbook->id == puser->bookid3)
    {
        printf("Sorry, you already have a copy of this book on loan.\n");
        return 1;
    }
    if (puser->length == 0)
    {
        pbook->copies--;
        puser->bookid1 = pbook->id;
        puser->length++;
        pbook->state = 1;

        pborrowbook->length++;
        pborrowbook->array = pbook;
        pb = pborrowbook->array;
        pb->nextfind = NULL;
        return 0;
    }
    if (puser->length == 1)
    {
        pbook->copies--;
        puser->bookid2 = pbook->id;
        puser->length++;
        pbook->state = 1;

        pborrowbook->length++;
        pborrowbook->array->nextfind = pbook;
        pb->nextfind = pborrowbook->array;
        pb->nextfind->nextfind = NULL;
        return 0;
    }
    if (puser->length == 2)
    {
        pbook->copies--;
        puser->bookid3 = pbook->id;
        puser->length++;
        pbook->state = 1;

        pborrowbook->length++;
        pborrowbook->array->nextfind->nextfind = pbook;
        pb->nextfind->nextfind = pborrowbook->array;
        pb->nextfind->nextfind = NULL;
        return 0;
    }
}

int return_book(Book *pbook, User *puser, BookArray *pborrowbook)
{
    if (pbook->id == puser->bookid3)
    {
        pbook->copies++;
        puser->bookid3 = 0;
        puser->length--;
        pbook->state = 0;

        pborrowbook->length--;
        pborrowbook->array->nextfind->nextfind = NULL;
        return 0;
    }
    if (pbook->id == puser->bookid2)
    {
        pbook->copies++;
        puser->bookid2 = 0;
        puser->length--;
        pbook->state = 0;

        pborrowbook->array->nextfind = NULL;
        pborrowbook->length--;
        return 0;
    }
    if (pbook->id == puser->bookid1)
    {
        pbook->copies++;
        puser->bookid1 = 0;
        puser->length--;
        pbook->state = 0;

        pborrowbook->array = NULL;
        pborrowbook->length--;
        return 0;
    }
}

void printmenu() //主菜单
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
    User *pu;
    pu = puserarray->array;
    if (puserarray->length == 0)
    {
        return 0;
    }
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
    User *pu;
    pu = puserarray->array;
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

void usmenu(const char *username) //用戶菜單
{
    printf("(Logged in as: %s)\n", username);
    printf("1)Borrow a book\n");
    printf("2)Return a book\n");
    printf("3)Search for books\n");
    printf("4)Display all books\n");
    printf("5)Log out\n");
    printf(" Option:");
}

void display_all_books(BookArray *pbookarray) //展示图书
{
    Book *pb;
    pb = pbookarray->array;
    printf("ID    Title           Authors         Year  Copies\n");
    for (int i = 0; i < pbookarray->length; i++)
    {
        printf("%i     ", pb->id);
        int a = strlen(pb->title);
        printf("%s", pb->title);
        for (int i = 0; i < 16 - a; i++)
        {
            printf(" ");
        }
        printf("%s", pb->authors);
        int b = strlen(pb->authors);
        for (int i = 0; i < 16 - b; i++)
        {
            printf(" ");
        }
        printf("%i  ", pb->year);
        printf("%i", pb->copies);
        pb = pb->next;
    }
}

void print_borrow_book(BookArray *pborrowbook)
{
    Book *pb;
    pb = pborrowbook->array;
    printf("ID    Title           Authors         Year  Copies\n");
    for (int i = 0; i < pborrowbook->length; i++)
    {
        printf("%i     ", pb->id);
        int a = strlen(pb->title);
        printf("%s", pb->title);
        for (int i = 0; i < 16 - a; i++)
        {
            printf(" ");
        }
        printf("%s", pb->authors);
        int b = strlen(pb->authors);
        for (int i = 0; i < 16 - b; i++)
        {
            printf(" ");
        }
        printf("%i  ", pb->year);
        printf("%i", pb->copies);
        pb = pb->next;
    }
}

int main()
{
    int option, year1, copies1, id, state; //returned book id
    char *username, *password, *title, *author, *year, *copies, *option1;
    BookArray *pbookarray;
    BookArray *pfindbook;
    BookArray *pborrowbook;
    UserArray *puserarray;
    UserArray head;

    FILE *fbookarray;
    FILE *fuserarray;

    User *a;
    a = (User *)malloc(sizeof(User));
    Book *b;
    b = (Book *)malloc(sizeof(Book));

    username = (char *)malloc(100 * sizeof(char));
    password = (char *)malloc(100 * sizeof(char));
    title = (char *)malloc(100 * sizeof(char));
    author = (char *)malloc(100 * sizeof(char));
    year = (char *)malloc(100 * sizeof(char));
    copies = (char *)malloc(100 * sizeof(char));
    option1 = (char *)malloc(100 * sizeof(char));
    puserarray = (UserArray *)malloc(sizeof(UserArray));
    puserarray->array = (User *)malloc(sizeof(User));
    puserarray->length = 0;
    pbookarray = (BookArray *)malloc(sizeof(BookArray));
    pbookarray->array = (Book *)malloc(sizeof(Book));
    pbookarray->length = 0;
    pfindbook = (BookArray *)malloc(sizeof(BookArray));
    pfindbook->array = (Book *)malloc(sizeof(Book));
    pfindbook->length = 0;
    pborrowbook = (BookArray *)malloc(sizeof(BookArray));
    pborrowbook->array = (Book *)malloc(sizeof(Book));
    pborrowbook->length = 0;

    fbookarray = fopen("book.bin", "wb");
    fuserarray = fopen("user.bin", "wb");
    load_books(fbookarray, pbookarray);
    load_users(fuserarray, puserarray);

mainmenu:
    printmenu();
    scanf("%s", option1);
    while (strcmp(option1, "1") != 0 && strcmp(option1, "2") != 0 && strcmp(option1, "3") != 0 && strcmp(option1, "4") != 0 && strcmp(option1, "5") != 0)
    {
        printf("Sorry, the option you entered was invalid, please try again.\n");
        printmenu();
        scanf("%s", option1);
    }
    option = atoi(option1);
    if (option == 1) //主菜单 注册账户
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

        a->username = (char *)malloc(100 * sizeof(char));
        a->password = (char *)malloc(100 * sizeof(char));
        strcpy(a->username, username); //給指針賦值
        strcpy(a->password, password);
        a->bookid1 = 0;
        a->bookid2 = 0;
        a->bookid3 = 0;
        a->length = 0;
        a->next = NULL;
        if (add_users(a, puserarray) == 0)
        {
            printf("Registered library account successfully!\n");
        }
        else
        {
            printf("The username is already in use!\n");
        }
        goto mainmenu;
    }

    else if (option == 2) // 主菜单 登录账户
    {
        printf("Please enter your username:");
        scanf("%s", username);
        printf("Please enter your password:");
        scanf("%s", password);
        if (strcmp(username, "librarian") == 0 && strcmp(password, "librarian") == 0) //登入图书管理员
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
            if (option == 1) //图书管理员增加书籍
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

                b->title = (char *)malloc(100 * sizeof(char));
                b->authors = (char *)malloc(100 * sizeof(char));
                strcpy(b->authors, author); //給指針賦值
                strcpy(b->title, title);
                b->year = year1;
                b->copies = copies1;
                b->state = 0;
                b->next = NULL;
                if (add_book(b, pbookarray) == 1)
                {
                    printf("This book has existed, please try again.\n");
                    goto baa;
                }
                printf("Book was successfully added!");
                goto ba;
            }
            if (option == 2) //图书管理员删除图书
            {
                printf("Please enter the id of the book you wish to remove:");
                fflush(stdin);
                scanf("%i", &id);
                if (remove_book(id, pbookarray) == 0)
                {
                    printf("This book was successfully removed.\n");
                    goto ba;
                }
                else
                {
                    printf("Fail to delete.\n");
                    goto ba;
                }
            }
            if (option == 3) //搜索图书
            {
                printf("Loading search menu...\n");
            bac:
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
                    fflush(stdin);
                    gets(title);
                    find_book_by_title(title, pbookarray, pfindbook);
                    goto bac;
                }
                if (option == 2)
                {
                    printf("Please enter author:");
                    fflush(stdin);
                    gets(author);
                    find_book_by_author(author, pbookarray, pfindbook);
                    goto bac;
                }
                if (option == 3)
                {
                    printf("Please enter year:");
                    fflush(stdin);
                    gets(year);
                    year1 = atoi(year);
                    find_book_by_year(year1, pbookarray, pfindbook);
                    goto bac;
                }
                if (option == 4)
                {
                    printf("Returning to previous menu...\n");
                    goto ba;
                }
            }
            if (option == 4) //展示图书
            {
                display_all_books(pbookarray);
                goto ba;
            }
            if (option == 5) //退回主界面
            {
                printf("Logging out...\n");
                goto mainmenu;
            }
        }
        if (checkusersame(username, puserarray) == 1 && checkpasssame(password, puserarray) == 1) //登入用户
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
            if (option == 1) //用户借书
            {
                printf("Enter the ID number of the book you wish to borrow:");
                scanf("%i", &id);
                while (pbookarray->array != NULL)
                {
                    if (pbookarray->array->id == id)
                    {
                        break;
                    }
                    pbookarray->array = pbookarray->array->next;
                }
                if (pbookarray->array->copies == 0)
                {
                    printf("There is no this book.");
                    goto bb;
                }
                while (puserarray->array != NULL)
                {
                    if (strcmp(puserarray->array->username, username) == 0)
                    {
                        break;
                    }
                    puserarray->array = puserarray->array->next;
                }
                if (puserarray->array->length == 3)
                {
                    printf("You can not borrow books before you return the book you borrowed.");
                    goto bb;
                }
                if (pbookarray->array->id == id)
                {
                    if (borrow_book(pbookarray->array, puserarray->array, pborrowbook) == 0)
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
            if (option == 2) //用户还书
            {
                if (pborrowbook->length == 0)
                {
                    printf("You haven't borrowed the book yet.\n");
                    goto bb;
                }
                print_borrow_book(pborrowbook);
                printf("Please enter the id of the book you wish to return.");
                scanf("%i", &id);
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
                    if (strcmp(puserarray->array->username, username) == 0)
                    {
                        break;
                    }
                    puserarray->array = puserarray->array->next;
                }
                if (pbookarray->array->id == id)
                {
                    return_book(pbookarray->array, puserarray->array, pborrowbook);
                    printf("You have successfully returned the book!\n");
                    goto bb;
                }
                else
                {
                    printf("This book doesn't exist here.\n");
                    goto bb;
                }
            }
            if (option == 3) //用户查书
            {
                printf("Loading search menu...\n");
            bbc:
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
                    fflush(stdin);
                    gets(title);
                    find_book_by_title(title, pbookarray, pfindbook);
                    goto bbc;
                }
                if (option == 2)
                {
                    printf("Please enter author:");
                    fflush(stdin);
                    gets(author);
                    find_book_by_author(author, pbookarray, pfindbook);
                    goto bbc;
                }
                if (option == 3)
                {
                    printf("Please enter year:");
                    fflush(stdin);
                    gets(year);
                    year1 = atoi(year);
                    find_book_by_year(year1, pbookarray, pfindbook);
                    goto bbc;
                }
                if (option == 4)
                {
                    printf("Returning to previous menu...\n");
                    goto bb;
                }
            }
            if (option == 4) //展示书籍
            {
                display_all_books(pbookarray);
                goto bb;
            }
            if (option == 5) //用户返回上一页
            {
                printf("Logging out...\n");
                goto mainmenu;
            }
        }
        else
        {
            printf("The user name does not exist, please try again");
            goto mainmenu;
        }
    }

    else if (option == 3) //主菜单 查询书籍
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
            fflush(stdin);
            gets(title);
            find_book_by_title(title, pbookarray, pfindbook);
            goto bac;
        }
        if (option == 2)
        {
            printf("Please enter author:");
            fflush(stdin);
            gets(author);
            find_book_by_author(author, pbookarray, pfindbook);
            goto bac;
        }
        if (option == 3)
        {
            printf("Please enter year:");
            fflush(stdin);
            gets(year);
            year1 = atoi(year);
            find_book_by_year(year1, pbookarray, pfindbook);
            goto bac;
        }
        if (option == 4)
        {
            printf("Loading main menu...\n");
            goto mainmenu;
        }
    }

    else if (option == 4) //主菜单 展示书籍
    {
        display_all_books(pbookarray);
        goto mainmenu;
    }

    else // 主菜单 退出程序
    {
        printf("Thank you for using the library!\n");
        printf("Goodbye!");

        store_books(fbookarray, pbookarray);
        store_users(fuserarray, puserarray);

        for (int i = 0; i < pbookarray->length; i++)
        {
            free(pbookarray->array);
            pbookarray->array = pbookarray->array->next;
        }
        for (int i = 0; i < puserarray->length; i++)
        {
            free(puserarray->array);
            puserarray->array = puserarray->array->next;
        }
        free(puserarray);
        free(puserarray->array);
        free(pbookarray);
        free(pbookarray->array);
        free(pfindbook);
        free(pfindbook->array);
        free(pborrowbook);
        free(pborrowbook->array);
        free(a);
        free(b);

        fclose(fbookarray);
        fclose(fuserarray);

        return 0;
    }
}
