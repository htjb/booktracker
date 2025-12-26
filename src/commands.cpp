#include <iostream>
#include <string>
#include "book.h"
#include "database.h"

using namespace std;

void add(string title, int databaseLength) {

    struct Book newBook;
    newBook.title = title;
    newBook.id = databaseLength + 1;
    cout << "Author: ";
    getline(cin,newBook.author);
    cout << "Day started: ";
    cin >> newBook.dayStarted;
    cout << "Status (e.g., reading, completed): ";
    cin >> newBook.status;

    cout << "Added book: " << newBook.title << " by " << newBook.author << " (Started on: " << newBook.dayStarted << ")" << endl;

    saveBook(newBook);
}

void list() {
    vector<Book> books = loadBooks();
    cout << "ID | Title | Author | Day Started | Status " << endl;
    cout << "-------------------------------------" << endl;
    for (int i = 0; i < books.size(); i++) {
        cout << books[i].id << " | " << books[i].title << " | " << books[i].author << " | " << books[i].dayStarted << " | " << books[i].status << endl;
    }
}
