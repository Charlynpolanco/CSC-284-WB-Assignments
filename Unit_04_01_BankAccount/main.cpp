// Unit_04_01_BankAccount.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "BankAccount.h"
#include <iostream>

using namespace std;


int main() {
    cout << "Creating accounts...\n\n";

    // Create Alice and Bob
    BankAccount alice("Alice", 1000.0);
    BankAccount bob("Bob", 500.0);

   cout << "\nInitial account info:\n";
    alice.printAccountInfo();
    cout << endl;
    bob.printAccountInfo();

    cout << endl;

    // Deposit and Withdraw
    alice.deposit(200.0);

    bob.withdraw(100.0);

    cout << "\nUpdated account info:\n";
    alice.printAccountInfo();
    cout << endl;
    bob.printAccountInfo();
    cout << endl;
    cout << "Total active accounts: " << BankAccount::getTotalAccounts() << "\n\n";

    cout << "Entering block scope...\n";
    {
        BankAccount temp("Temp", 0.0);
        cout << "Total active accounts: " << BankAccount::getTotalAccounts() << "\n\n";
    }
    cout << "Leaving block scope...\n";
    cout << "Total active accounts after block: " << BankAccount::getTotalAccounts() << "\n\n";

    cout <<("Alice transfers $250 to Bob...\n");
    alice.transfer(bob, 250.0);

    cout << "\nFinal account info:\n";
    alice.printAccountInfo();
    cout << endl;
    bob.printAccountInfo();

    cout << ("Exiting program...\n");

    return 0;
}
