#pragma once
#include <string>
class BankAccount {

private: 
	std::string accountHolder;
	int accountNumber;
	double balance = 0;
	static int totalAccounts;
	static int nextAccountNumber;

public:
	//Constructors
	BankAccount(); //default constructor
	BankAccount(const std::string nameConstructor, double balanceConstructor);
	//desctructors
	~BankAccount();

	//accessors
	std::string getAccountHolder() const;
	int getAccountNumber() const;
	double getBalance() const;
	
	//member Functions

	void deposit(double amount);
	void withdraw(double amount);
	void printAccountInfo() const;
	void transfer(BankAccount& toAccount, double amount);

	//static Function
	static int getTotalAccounts();
};