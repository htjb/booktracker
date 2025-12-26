#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "book.h"
#include <vector>

void saveBook(Book b);

std::vector<Book> loadBooks();

#endif
