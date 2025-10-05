#include "BankAccount.h"
#include <iostream>
#include <iomanip>

using namespace std;
//static members
int BankAccount::totalAccounts = 0;
int BankAccount::nextAccountNumber = 5001;
//constructors 
BankAccount::BankAccount() {
	accountHolder = "Unknown";
	balance = 0.0;
	accountNumber = nextAccountNumber++;
	totalAccounts++;
}

BankAccount::BankAccount(string nameConstructor, double balanceConstructor) {
	accountNumber = nextAccountNumber++;
	totalAccounts++;
	accountHolder = nameConstructor;
	balance = balanceConstructor;

}
//End of constructors

//getters
string BankAccount::getAccountHolder() const {
	return accountHolder;
}
int BankAccount::getAccountNumber() const {
	return accountNumber;
}

double BankAccount::getBalance() const {
	return balance;
}
//end of getters



//adds money to the account
void BankAccount::deposit(double amount) {
	if (amount <= 0) {
		cout << "Deposit amount must be positive." << endl;
		return;
	}
	balance += amount;
	cout << accountHolder << " deposits $"
		 << fixed << setprecision(2) << amount << endl;
}

//Takes money away from account
void BankAccount::withdraw(double amount) {
	if (amount <= 0) {
		cout << "Withdrawal amount must be positive." << endl;
		return;
	}
	if (amount > balance) {
		cout << "Insufficient funds." << endl;
		return;
	}
	balance -= amount;
	cout << accountHolder << " withdraws $"
		 << fixed << setprecision(2) << amount << endl;
}

//displays the information of the account 
void BankAccount::printAccountInfo() const {
	cout << "Account Holder: " << accountHolder << endl;
	cout << "Account Number: " << accountNumber << endl;
	cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
}

//Moves money from one account to another
void BankAccount::transfer(BankAccount& toAccount, double amount) {
	if (amount <= 0) {
		cout << "Transfer amount must be positive." << endl;
		return;
	}
	if (amount > balance) {
		cout << "Transfer failed: insufficient funds." << endl;
		return;
	}

	balance -= amount;
	toAccount.balance += amount;

	cout << "Transferred $" << fixed << setprecision(2) << amount
		 << " from " << accountHolder
		 << " to " << toAccount.accountHolder << endl;
}


int BankAccount::getTotalAccounts() {
	return totalAccounts;
}

//Destructor
BankAccount::~BankAccount() {
	cout << "Destructor called for account " << accountNumber << endl;
	totalAccounts--;
}


