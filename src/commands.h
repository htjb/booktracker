#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>
#include "book.h"

void addBook(std::string title, int databaseLength);
void deleteBook(int id, std::vector<Book> books);
void list();

#endif 
