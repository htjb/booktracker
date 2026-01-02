/* Help function for BookTracker.
*
* Author: Harry Bevins
*/

#include <iostream>
#include <iomanip>

using namespace std;

void displayHelp() {
    /* Function to display the help menu for BookTracker. */
    cout << "BookTracker Help Menu" << endl;
    cout << "----------------------" << endl;
    cout << "Commands:" << endl;
    cout << left << setw(25) << "add 'book_title'" << "Add a new book to your collection." << endl;
    cout << left << setw(25) << "delete (del) <ID>" << "Remove a book from your collection." << endl;
    cout << left << setw(25) << "list (ls)" << "List all books in your collection." << endl;
    cout << left << setw(25) << "show <ID>" << "Display detailed information about a specific book." << endl;
    cout << left << setw(25) << "modify (mod) <ID> <section> <new_value>" << "Modify a specific section of a book's details." << endl;
    cout << left << setw(25) << "version" << "Display the current version of BookTracker." << endl;
    cout << left << setw(25) << "stats" << "Show reading statistics." << endl;
    cout << left << setw(25) << "plot" << "Generate plots of your reading data." << endl;
    cout << left << setw(25) << "help" << "Display this help menu." << endl;
}
