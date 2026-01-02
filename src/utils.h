#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "book.h"

void checkStatus(Book &newBook);
void checkRating(Book &newBook);
bool checkDate(std::string date);
int filterDateStatus(std::vector<Book> books, std::string date, std::string status);
std::string fit(const std::string& s, size_t w);
int terminalWidth();
std::vector<std::string> wrapText(const std::string &text, int width);

#endif
