#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "book.h"

void checkStatus(Book &newBook);
bool checkDate(std::string date);
int filterDateStatus(std::string homeDir, std::string date, std::string status);

#endif
