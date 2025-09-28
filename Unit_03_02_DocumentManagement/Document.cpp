#include "Document.h"
#include <memory>
#include <iostream>
#include <print>

using namespace std;

Document::Document(const string& name, const string& insides) {
    title = name;
    content = make_unique<string>(insides);
    print("Document \"{}\" created.\n", title);
}
Document::~Document() {
    print("Document \"{}\" destroyed.\n", title);
}
void Document::show() {
    println("Title: {}", title);
    println("Content: {}", *content);
}
void Document::edit(const string& editContent) {
    *content = editContent;
}

unique_ptr<Document> createDocument(const string& title, const string& content) {
    return make_unique<Document>(title, content);
}

shared_ptr<Document> createSharedDocument(const string& title, const string& content) {
    return make_shared<Document>(title, content);
}