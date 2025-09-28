#include "Document.h"
#include <iostream>
#include <string>
#include <print>

using namespace std;


int main() {
    cout << "=== Unique_ptr demonstration ===\n";
    unique_ptr<Document> doc1 = createDocument("My Unique Doc", "Initial content");
    doc1->show();

    // Transfer ownership
    unique_ptr<Document> doc2 = move(doc1);
    if (!doc1) {
        cout << "doc1 no longer owns the document\n";
    }
    doc2->edit("Updated content");
    doc2->show();

    cout << "\n=== Shared_ptr demonstration ===\n";
    shared_ptr<Document> sharedDoc = createSharedDocument("Shared Doc", "Shared content");
    {
        shared_ptr<Document> viewer = sharedDoc;  // second owner
        viewer->show();
        viewer->edit("Edited by viewer");
    } // viewer goes out of scope, document still exists

    sharedDoc->show();
    cout << "End of main()\n";

    return 0;
}
