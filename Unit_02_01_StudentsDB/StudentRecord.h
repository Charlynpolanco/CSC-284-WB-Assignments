#pragma once

#include <string>

namespace Records {

	class Student
	{
	private:
		inline static int nextId{ 101 };
		int id;
		std::string Name;
		int age;
		std::string major;
		std::string email;

	public:
	
		// Constructors
		Student();
		Student(std::string studentName, int studentAge, std::string studentMajor, std::string studentEmail);
		void display() const; // Prints students info

		//getters and setters
		void setName(std::string n);
		void setAge(int a);
		void setMajor(std::string m);
		void setEmail(std::string e);
		
		int getId() const;
		std::string getName() const;
		int getAge() const;
		std::string getMajor() const;
		std::string getEmail() const;
	};
}