//Name: Charly Nunez Polanco
//Email: Charly.nunezPolanco@bhcc.edu
//Unit 2, Assignment 1: Student Records Manager
#include "StudentRecord.h"
#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <string_view>
#include <set>
#include <algorithm>
#include <format>

using namespace std;
using namespace Records;

//Proto functions
void addStudent(vector<Student>& record);
void displayStudents(vector<Student>& record);
void IdSearch(vector<Student>& record);
void nameSearch(vector<Student>& record);
void studentPerMajor(vector<Student>& record);
bool exit_Program(bool& stop_program);
void help();

/*******************************************************************
Asks the user to fill in the parameters and uses the               *
constructor of the class Student to initialize the object          *
validates input for age.                                           *
*******************************************************************/
void addStudent(vector<Student>& record) {
	
	int age;
	std::string name, major, email;

	cout << "Enter Student Name: ";
	getline(cin, name);
    //loop to validate age input
    while (true) {
        cout << "Enter Student age: ";
        cin >> age;

        if (cin.fail() || age <= 0) {
            cin.clear(); 
            cin.ignore(1000, '\n');
            cout << "Invalid age. Please enter a non-negative integer.\n";
        }
        else {
            cin.ignore(1000, '\n'); // discard leftover newline
            break; // valid age entered
        }
    }

	cout << "Enter Student major: ";
	getline(cin, major);

	cout << "Enter Student email: ";
	getline(cin, email);
    

	record.emplace_back(Student(name, age, major, email));
}
/*******************************************************************
Displays the info of all the current students in the records       *
formatted in a table design                                        *
*******************************************************************/
void displayStudents(vector<Student>& record) {
    if (record.empty()) {
        cout << "No student data has been found.\n";
        return; 
    }
    cout << std::format("{:<6} {:<20} {:<6} {:<12} {}\n",
        "ID",
        "Name",
        "Age",
        "Major",
        "Email");
    cout << "----------------------------------------------------------\n";
    for (const auto& student : record) {
        student.display();
    }
}

/*******************************************************************
Asks the user for an Id number of a student.                       *
Uses ranges to find the Id and then prints the info of that student*
If no student was found with that Id, prints out                   *
an appropiate error message.                                       *
*******************************************************************/
void IdSearch(vector<Student>& record){
    int searchID;
    cout << "Enter ID to search for: ";
    cin >> searchID;
    cin.ignore(1000, '\n');

    auto it = ranges::find_if(record,
        [searchID](const Student& s) { return s.getId() == searchID; });

    if (it != record.end()) {
        it->display();  
    }
    else {
        std::cout << "Student not found.\n";
    }
}
/*******************************************************************
Asks the user for the name of a student.                           *
Uses ranges and string_view to find the name                       *
and then prints the info of that student                           *
If no student was found with that name, prints out                 *
an appropiate error message.                                       *
*******************************************************************/
void nameSearch(vector<Student>& record) {
    string nameSearch;
    cout << "Enter name to search for: ";
    getline(cin, nameSearch);
    string_view nameView(nameSearch);

    auto it = std::ranges::find_if(record,
        [nameView](const Student& s) { return s.getName() == nameView; });

    if (it != record.end()) {
        it->display();
    }
    else {
        std::cout << "Student not found.\n";
    }
}
/*******************************************************************
Displays the number of students in each major                      *
that is currently in the records                                   *
*******************************************************************/
void studentPerMajor(vector<Student>& record) {
    if (record.empty()) {
        cout << "No student data has been found.\n";
        return;
    }
    set<std::string> uniqueMajors;
    for (const auto& student : record) {
        uniqueMajors.insert(student.getMajor());
    }

    // Count students per major
    for (const auto& major : uniqueMajors) {
        int count = std::ranges::count_if(record, [&major](const Student& s) {
            return s.getMajor() == major;
            });
        cout << major << ": " << count << "\n";
    }
}
/*******************************************************************
Displays the command list for this programs with descriptors       *
*******************************************************************/
void help() {
    cout << std::format("These are the available commands\n");

    cout << std::format("{:<6} {:<50}\n", "h", "prints out help menu");
    cout << std::format("{:<6} {:<50}\n", "a", "Adds a student to the records");
    cout << std::format("{:<6} {:<50}\n", "p", "Prints all the student's information");
    cout << std::format("{:<6} {:<50}\n", "i", "Searches a student's info by ID and prints it");
    cout << std::format("{:<6} {:<50}\n", "n", "Searches a student's info by name and prints it");
    cout << std::format("{:<6} {:<50}\n", "m", "Prints the number of students per major");
    cout << std::format("{:<6} {:<50}\n", "q", "Quits the program");
}
/*******************************************************************
Asks the user if they wish to end the program.                     *
If so, the program is terminated. Else the program continues       *
*******************************************************************/

bool exit_Program(bool& stop_program) {
    stop_program = false;

    string confirmation;
    cout << "Are you sure that you want to exit the program? ";

    cin >> confirmation;

    if (confirmation == "n") {
        stop_program = true;
    }
    else if (confirmation == "y") {
        cout << "Exit the program.";
        cout << endl;
    }
    cin.ignore(1000, '\n');
    return (stop_program);
}

int main()
{
    string command;
    bool keepRunning = true;
    vector<Student> students;

    //command loop
    while (keepRunning) {
        cout << "Enter command (or 'h' for help): ";
        getline(cin, command);

        if (command == "a") {
            addStudent(students);
        }
        else if (command == "p") {
            displayStudents(students);
        }
        else if (command == "i") {
            IdSearch(students);
        }
        else if (command == "n") {
            nameSearch(students);
        }
        else if (command == "m") {
            studentPerMajor(students);
        }
        else if (command == "h") {
            help();
        }
        else if (command == "q") {
            exit_Program(keepRunning);

        }
        else {
            cout << "No valid command inputted";
            cout << endl;
        }
    }

    return 0;

}

