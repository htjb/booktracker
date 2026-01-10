#include "book.h"
#include <iostream>
#include <vector>

using namespace std;

void stats(vector<Book> &books) {
  /* Function to display statistics about the book collection.
   * Params:
   *   books - vector of Book structs representing the collection
   */

  int totalBooks = books.size();
  int readingCount = 0;
  int readCount = 0;
  int tbrCount = 0;
  int dnfCount = 0;
  int numberOfPages = 0;

  vector<int> ratings;
  for (const auto &book : books) {
    if (book.status == "reading") {
      readingCount++;
    } else if (book.status == "read") {
      readCount++;
      ratings.push_back(stoi(book.rating));
      numberOfPages += book.pages;
    } else if (book.status == "tbr") {
      tbrCount++;
    } else if (book.status == "dnf") {
      dnfCount++;
    }
  }

  cout << "Total books: " << totalBooks << endl;
  cout << "Books read: " << readCount << endl;
  if (readCount > 0) {
    float averageRating = 0.0;
    if (!ratings.empty()) {
      int sumRatings = 0;
      for (int r : ratings) {
        sumRatings += r;
      }
      averageRating = static_cast<float>(sumRatings) / ratings.size();
    }
    cout << "   With an average rating of: " << averageRating << endl;
  }
  cout << "Currently reading: " << readingCount << endl;
  cout << "To be read (TBR): " << tbrCount << endl;
  cout << "Did not finish (DNF): " << dnfCount << endl;
  cout << "Number of pages read: " << numberOfPages << endl;
}
