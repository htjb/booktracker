#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "book.h"
#include <vector>

void saveBook(Book b, std::string homeDir);
std::vector<Book> loadBooks(std::string homeDir);

#endif
