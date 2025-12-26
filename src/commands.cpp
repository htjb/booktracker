#include <iostream>
#include <fstream>
#include <string>
#include "book.h"
#include "database.h"

using namespace std;

void addBook(string title, int databaseLength) {

    struct Book newBook;
    newBook.title = title;
    newBook.id = databaseLength + 1;
    cout << "Author: ";
    getline(cin,newBook.author);
    cout << "Day started: ";
    cin >> newBook.dayStarted;
    cout << "Status (e.g., reading, completed): ";
    cin >> newBook.status;
    cout << "Day completed (if applicable, else leave blank): ";
    cin >> newBook.dayCompleted;

    cout << "Added book: " << newBook.title << " by " << newBook.author << " (Started on: " << newBook.dayStarted << ")" << endl;

    saveBook(newBook);
}

void deleteBook(int id, vector<Book> books) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i].id == id) {
            books.erase(books.begin() + i);
            cout << "Deleted book with ID: " << id << endl;
        }
    }
    
    ofstream out("books.txt", ios::trunc);
    for (Book b : books) {
        out << b.id << "|" <<  b.title << "|" 
            << b.author << "|" << b.dayStarted << 
            "|" << b.dayCompleted << "|" << b.status << "\n";
    }
}

void list() {
    vector<Book> books = loadBooks();
    cout << "ID | Title | Author | Day Started | Day Completed | Status " << endl;
    cout << "-------------------------------------" << endl;
    for (int i = 0; i < books.size(); i++) {
        cout << books[i].id << " | " << books[i].title << " | " << books[i].author << " | " << books[i].dayStarted << " | " << books[i].dayCompleted << " | " << books[i].status << endl;
    }
}
