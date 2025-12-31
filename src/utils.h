#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "book.h"

void checkStatus(Book &newBook);
bool checkDate(std::string date);
int filterDateStatus(std::vector<Book> books, std::string date, std::string status);
std::string fit(const std::string& s, size_t w);

#endif
