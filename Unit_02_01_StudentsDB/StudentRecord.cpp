#include "StudentRecord.h"
#include <format>
#include <iostream>
using namespace std;

namespace Records {
	

	//default constructor
	Student::Student()
	{
		id = 0;
		Name = "";
		age = 0;
		major = "";
		email = "";
	}
	//Constructor
	Student::Student(std::string studentName, int studentAge, std::string studentMajor, std::string studentEmail)
	{
	
		id = nextId++;
		Name = studentName;
		age = studentAge;
		major = studentMajor;
		email = studentEmail;
	}
	void Student::setName(std::string n) 
	{
		Name = n;
	}

	void Student::setAge(int a) 
	{
		age = a;
	}
	void Student::setMajor(std::string m) 
	{
		major = m;
	}
	void Student::setEmail(std::string e) 
	{
		email = e;
	}

	int Student::getId() const{
		return id;
	}
	std::string Student::getName() const
	{
		return Name;
	}
	int Student::getAge() const 
	{
		return age;
	}
	std::string Student::getMajor() const 
	{
		return major;
	}
	std::string Student::getEmail() const 
	{
		return email;
	}
	void Student::display() const 
	{

		std::cout << std::format("{:<6} {:<20} {:<6} {:<12} {}\n",
			id,
			Name,
			age,
			major,
			email);
		
	}
}