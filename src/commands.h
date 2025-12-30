#ifndef COMMANDS_H
#define COMMANDS_H

#include "book.h"
#include <iostream>
#include <string>
#include <vector>

void addBook(std::string title, int databaseLength);
void deleteBook(int id, std::vector<Book> books);
void list(std::vector<Book> books);
void showBook(int id, std::vector<Book> books);
void modifyBook(int id, std::string section, std::string newValue, std::vector<Book> books);
void plot();

#endif
