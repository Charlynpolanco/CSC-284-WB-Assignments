#include "Library.h"
#include <iostream>
#include <string>
#include <vector>
#include <format>

using namespace std;

/*******************************************************************
Displays the menu commands for the Library program               *
*******************************************************************/
void displayHelp() {
    cout << "\n=== Library Commands ===\n";
    cout << std::format("{:<6} {:<50}\n", "a", "Add a new book to the library");
    cout << std::format("{:<6} {:<50}\n", "r", "Remove a book by title");
    cout << std::format("{:<6} {:<50}\n", "f", "Find a book by title and display info");
    cout << std::format("{:<6} {:<50}\n", "d", "Display all books");
    cout << std::format("{:<6} {:<50}\n", "p", "Display books by author");
    cout << std::format("{:<6} {:<50}\n", "g", "Display books by genre (sorted by year)");
    cout << std::format("{:<6} {:<50}\n", "y", "Display books published after a specific year");
    cout << std::format("{:<6} {:<50}\n", "q", "Quit the program\n");
}

/*******************************************************************
Asks user for confirmation before exiting                         *
*******************************************************************/
bool confirmExit() {
    string input;
    cout << "Are you sure you want to exit? (y/n): ";
    getline(cin, input);
    return (input == "y" || input == "Y");
}

/*******************************************************************
Main command loop for Library management                           *
*******************************************************************/
int main() {
    Library library;
    string command;

    cout << "Welcome to the Library Manager!\n";
    cout << "Type 'h' for help.\n";

    while (true) {
        cout << "\nEnter command: ";
        getline(cin, command);

        if (command == "a") {
            string title, author, genre;
            int year;

            cout << "Enter book title: "; getline(cin, title);
            cout << "Enter book author: "; getline(cin, author);
            cout << "Enter year published: "; cin >> year; cin.ignore(1000, '\n');
            cout << "Enter book genre: "; getline(cin, genre);

            library.add_book(Book(title, author, year, genre));
            cout << "Book added!\n";
        }
        else if (command == "r") {
            string title;
            cout << "Enter title to remove: "; getline(cin, title);
            library.remove_book(title);
        }
        else if (command == "f") {
            string title;
            cout << "Enter title to find: "; getline(cin, title);
            Book* found = library.find_book(title);
            if (found) found->display();
            else cout << "Book not found.\n";
        }
        else if (command == "d") {
            if (library.get_books_after_year(0).empty()) { // check if library is empty
                cout << "No books in library.\n";
            }
            else {
                library.display_all_books();
            }
        }
        else if (command == "p") {
            string author;
            cout << "Enter author: "; getline(cin, author);
            vector<Book> booksByAuthor = library.get_books_by_author(author);

            if (!booksByAuthor.empty()) {
                for (const auto& b : booksByAuthor) b.display();
            }
            else {
                cout << "No books by this author.\n";
            }
        }
        else if (command == "g") {
            string genre;
            cout << "Enter genre: "; getline(cin, genre);
            vector<Book> booksByGenre = library.get_books_by_genre_sorted(genre);

            if (!booksByGenre.empty()) {
                for (const auto& b : booksByGenre) b.display();
            }
            else {
                cout << "No books in this genre.\n";
            }
        }
        else if (command == "y") {
            int year;
            cout << "Enter year: "; cin >> year; cin.ignore(1000, '\n');
            vector<Book> recentBooks = library.get_books_after_year(year);

            if (!recentBooks.empty()) {
                for (const auto& b : recentBooks) b.display();
            }
            else {
                cout << "No books published after " << year << ".\n";
            }
        }
        else if (command == "h") {
            displayHelp();
        }
        else if (command == "q") {
            if (confirmExit()) break;
        }
        else {
            cout << "Invalid command. Type 'h' for help.\n";
        }
    }

  
    return 0;
}