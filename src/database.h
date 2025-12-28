#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "book.h"
#include <vector>

void saveBook(Book b, std::string homeDir);
std::vector<Book> loadBooks(std::string homeDir);
void saveAllBooks(const std::vector<Book> books, const std::string homeDir);

#endif
