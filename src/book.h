#ifndef BOOK_H
#define BOOK_H

#include <string>

struct Book {
    int id;
    std::string title;
    std::string author;
    std::string dayStarted;
    std::string dayCompleted;
    std::string status;
};

#endif
