#pragma once
#include "Book.h"
#include <vector>
#include <string>

class Library {
private:
    std::vector<Book> books;

public:

    void add_book(const Book& book);
    void remove_book(const std::string& title);
    Book* find_book(const std::string& title);
    //getters
    std::vector<Book> get_books_by_author(const std::string& author) const;
    std::vector<Book> get_books_by_genre(const std::string& genre) const;
    std::vector<Book> get_books_after_year(int year) const;
    std::vector<Book> get_books_by_genre_sorted(const std::string& genre) const;
    //prints all the books saved in the vector
    void display_all_books() const;
};