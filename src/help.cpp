/* Help function for BookTracker.
 *
 * Author: Harry Bevins
 */

#include "utils.h"
#include <iomanip>
#include <iostream>

using namespace std;

void displayHelp() {
  /* Function to display the help menu for BookTracker. */

  int termWidth = terminalWidth();
  int cmdWidth = 25;
  int descWidth = termWidth - cmdWidth - 5;

  if (termWidth < 40) {
    cout << "Terminal width too small to display help menu." << endl;
    return;
  }

  /* Function to display the help menu for BookTracker. */
  cout << "BookTracker Help Menu" << endl;
  cout << string(termWidth, '-') << endl;
  cout << "Commands:" << endl;

  vector<pair<string, string>> commands = {
      {"add 'book_title'", "Add a new book to your collection."},
      {"delete (del) <ID>", "Remove a book from your collection."},
      {"list (ls)", "List all books in your collection."},
      {"show <ID>", "Display detailed information about a specific book."},
      {"modify (mod) <ID> <section> 'new_value'",
       "Modify a specific section of a book's details."},
      {"version", "Display the current version of BookTracker."},
      {"stats", "Show reading statistics."},
      {"plot", "Generate plots of your reading data."},
      {"help", "Display this help menu."}};

  for (const auto &cmd : commands) {
    auto wrappedCMD = wrapText(cmd.first, cmdWidth);
    auto wrappedText = wrapText(cmd.second, descWidth);
    cout << left << setw(cmdWidth) << wrappedCMD[0] << wrappedText[0] << endl;
    int loopmax = max(wrappedCMD.size(), wrappedText.size());
    string wcmd;
    string wtext;
    for (size_t i = 1; i < loopmax; ++i) {
      wcmd = (i < wrappedCMD.size()) ? wrappedCMD[i] : "";
      wtext = (i < wrappedText.size()) ? wrappedText[i] : "";
      cout << left << setw(cmdWidth) << wcmd << wtext << endl;
    }
    cout << endl;
  }
}
