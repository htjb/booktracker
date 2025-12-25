#include <iostream>
#include <string>
#include "book.h"

using namespace std;

void add(string title) {

    struct Book newBook;
    cout << "Author: ";
    cin >> newBook.author;
    newBook.title = title;

    cout << newBook.title << " by " << newBook.author << " added!" << endl; 
}
