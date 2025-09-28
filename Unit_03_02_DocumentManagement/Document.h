#pragma once
#include <string>
#include <memory>
using namespace std;

class Document {
private:
	string title;
	unique_ptr<string> content;

public:
	//constructor
	Document(const string& name, const string& insides);
	//destructor
	~Document();
	//displays the document titel and content
	void show();
	//modifies the content
	void edit(const string&);
	
};

unique_ptr<Document> createDocument(const string& title, const string& content);
shared_ptr<Document> createSharedDocument(const string& title, const string& content);