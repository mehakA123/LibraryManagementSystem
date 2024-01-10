/*
LIBRARY MANAGEMENT SYSTEM
CREATED BY: Mehak Arora, 118978220
DATE: 12-08-2023
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct Book {
    int bookID;
    char title[100];
    char author[100];
    char genre[50];
    int quantity;
}Library;

void writeBook(Library book) {
    FILE* file = fopen("Library.csv", "a");
    fprintf(file, "%d,%s,%s,%s,%d\n", book.bookID, book.title, book.author, book.genre, book.quantity);
    fclose(file);
}

void searchBooks(char searchKey[]) {
    FILE* file = fopen("Library.csv", "r");
    Library book;
    int found = 0;

    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%d\n", &book.bookID, book.title, book.author, book.genre, &book.quantity) != EOF) {
        if (strstr(book.title, searchKey) || strstr(book.author, searchKey) || strstr(book.genre, searchKey)) {
            printf("Book ID: %d\nTitle: %s\nAuthor: %s\nGenre: %s\nQuantity: %d\n\n",
                book.bookID, book.title, book.author, book.genre, book.quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("No books found with the given search key.\n");
    }

    fclose(file);
}

void updateQuantity(int bookID, int change) {
    FILE* file = fopen("books.csv", "r");
    FILE* tempFile = fopen("temp.csv", "w");
    Library book;

    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%d\n", &book.bookID, book.title, book.author, book.genre, &book.quantity) != EOF) {
        if (book.bookID == bookID) {
            book.quantity += change;
        }
        fprintf(tempFile, "%d,%s,%s,%s,%d\n", book.bookID, book.title, book.author, book.genre, book.quantity);
    }

    fclose(file);
    fclose(tempFile);
    remove("books.csv");
    rename("temp.csv", "Library.csv");
}

void deleteBook(int bookID) {
    FILE* file = fopen("Library.csv", "r");
    FILE* tempFile = fopen("temp.csv", "w");
    Library book;

    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%d\n", &book.bookID, book.title, book.author, book.genre, &book.quantity) != EOF) {
        if (book.bookID != bookID) {
            fprintf(tempFile, "%d,%s,%s,%s,%d\n", book.bookID, book.title, book.author, book.genre, book.quantity);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove("Library.csv");
    rename("temp.csv", "Library.csv");
}

int main() {
    int choice;
    Library newBook;

    printf("Library Management System\n");

    while (1) {
        printf("\nOptions:\n");
        printf("1. Add Book\n");
        printf("2. Search Book\n");
        printf("3. Display All Books\n");
        printf("4. Check Book Availability\n");
        printf("5. Checkout Book/Return Book\n");
        printf("6. Delete Book\n");
        printf("7. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
 
            printf("Enter Book ID: ");
            scanf("%d", &newBook.bookID);
            printf("Enter Title: ");
            scanf(" %[^\n]s", newBook.title);
            printf("Enter Author: ");
            scanf(" %[^\n]s", newBook.author);
            printf("Enter Genre: ");
            scanf(" %[^\n]s", newBook.genre);
            printf("Enter Quantity: ");
            scanf("%d", &newBook.quantity);

            writeBook(newBook);
            printf("Book added successfully.\n");
            break;
        }

        else if (choice == 2) {
            printf("Enter search key: ");
            char searchKey[100];
            scanf(" %[^\n]s", searchKey);
            searchBooks(searchKey);
            break;
        }
        else if (choice == 3) {
            printf("List of all books:\n");
            FILE* file = fopen("books.csv", "r");
            char line[256];
            while (fgets(line, sizeof(line), file)) {
                printf("%s", line);
            }
            fclose(file);
            break;
        }
        else if (choice == 4) {
            printf("Enter Book ID to check availability: ");
            int checkID;
            scanf("%d", &checkID);
            FILE* checkFile = fopen("Library.csv", "r");
            Library checkBook;
            int found = 0;

            while (fscanf(checkFile, "%d,%[^,],%[^,],%[^,],%d\n", &checkBook.bookID, checkBook.title, checkBook.author, checkBook.genre, &checkBook.quantity) != EOF) {
                if (checkBook.bookID == checkID) {
                    printf("Book \"%s\" is %savailable.\n",
                        checkBook.title, checkBook.quantity > 0 ? "" : "not ");
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("Book with ID %d not found.\n", checkID);
            }

            fclose(checkFile);
            break;
        }
        else if (choice == 5) {
            printf("Enter Book ID to checkout/return book: ");
            int checkoutID;
            scanf("%d", &checkoutID);
            updateQuantity(checkoutID, +1);
            printf("Book checked out successfully.\n");
            break;
        }

        else if (choice == 6) {
            printf("Enter Book ID to delete: ");
            int deleteID;
            scanf("%d", &deleteID);
            deleteBook(deleteID);
            printf("Book deleted successfully.\n");
            break;
        }

        else if (choice == 7) {
            printf("Exiting...\n");
            return 0;
        }
        else{
            printf("Invalid choice.\n Please try again.\n");
        }
    }

    return 0;
}
