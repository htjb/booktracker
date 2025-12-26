// save and load functions for the database

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "book.h"

using namespace std;

void saveBook(Book b) {
    ofstream out("books.txt", ios::app);
    out << b.id << "|" <<  b.title << "|" << b.author << "|" << b.dayStarted << "\n";
}

vector<Book> loadBooks() {
    vector<Book> books;
    ifstream in("books.txt");
    string line;

    while (getline(in, line)) {
        stringstream ss(line);
        Book b;

        string idstr;
        getline(ss, idstr, '|');
        b.id = stoi(idstr);

        getline(ss, b.title, '|');
        getline(ss, b.author, '|');
        getline(ss, b.dayStarted, '|');
        books.push_back(b);
    }
    return books;
}
