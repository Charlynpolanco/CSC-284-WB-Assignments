#include "Library.h"
#include <iostream>
#include <algorithm>
#include <ranges>

using namespace std;

// Add a book to the library
void Library::add_book(const Book& book) {
    books.push_back(book);
}

// Remove a book by title
void Library::remove_book(const string& title) {
    vector<Book>::iterator it = remove_if(
        books.begin(), books.end(),
        [title](const Book& b) { return b.getTitle() == title; });

    if (it != books.end()) {
        books.erase(it, books.end());
        cout << "Book \"" << title << "\" removed.\n";
    }
    else {
        cout << "Book \"" << title << "\" not found.\n";
    }
}

// Find a book by title, returns pointer or nullptr
Book* Library::find_book(const string& title) {
    for (vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
        if (it->getTitle() == title) {
            return &(*it);
        }
    }
    return nullptr;
}

// Get all books by a specific author
vector<Book> Library::get_books_by_author(const string& author) const {
    vector<Book> result;
    for (vector<Book>::const_iterator it = books.begin(); it != books.end(); ++it) {
        if (it->getAuthor() == author) {
            result.push_back(*it);
        }
    }
    return result;
}

// Get all books by a specific genre
vector<Book> Library::get_books_by_genre(const string& genre) const {
    vector<Book> result;
    for (vector<Book>::const_iterator it = books.begin(); it != books.end(); ++it) {
        if (it->getGenre() == genre) {
            result.push_back(*it);
        }
    }
    return result;
}

// Display all books in the vector
void Library::display_all_books() const {
    for (vector<Book>::const_iterator it = books.begin(); it != books.end(); ++it) {
        it->display();
    }
}

// Get books published after a certain year using ranges
vector<Book> Library::get_books_after_year(int year) const {
    auto view = books | views::filter([year](const Book& b) { return b.getYear() > year; });
    vector<Book> result(view.begin(), view.end());
    return result;
}

// Get books by genre and sort them by year
vector<Book> Library::get_books_by_genre_sorted(const string& genre) const {
    auto genreView = books | views::filter([genre](const Book& b) { return b.getGenre() == genre; });
    vector<Book> result(genreView.begin(), genreView.end());
    sort(result.begin(), result.end(), [](const Book& a, const Book& b) { return a.getYear() < b.getYear(); });
    return result;
}