#pragma once
#include <string>

class Book {
private:
    std::string title;
    std::string author;
    int year;
    std::string genre;

public:
    //constructor
    Book(const std::string& title, const std::string& author, int year, const std::string& genre);
    //getters
    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;
    std::string getGenre() const;
    //display the content of the object
    void display() const;
};