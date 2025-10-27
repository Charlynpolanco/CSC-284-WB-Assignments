#include "Book.h"
#include <iostream>
using namespace std;
//constructor
Book::Book(const string& title, const string& author, int year, const string& genre)
    : title(title), author(author), year(year), genre(genre) {
}
//getters
string Book::getTitle() const { 
    return title; 
}
string Book::getAuthor() const {
    return author; 
}
int Book::getYear() const { 
    return year; 
}
string Book::getGenre() const {
    return genre; 
}
//prints the object's info
void Book::display() const {
    cout << title << " by " << author << " (" << year << ") [" << genre << "]\n";
}