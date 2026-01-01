/* Definition of the Book structure to represent book information.
 *
 * Author: Harry Bevins
 */
#ifndef BOOK_H
#define BOOK_H

#include <string>

struct Book {
  int id;
  std::string title;
  std::string author;
  std::string dayStarted;
  std::string dayCompleted;
  std::string dayAdded;
  std::string status;
  std::string rating;
  std::string notes;
};

#endif
