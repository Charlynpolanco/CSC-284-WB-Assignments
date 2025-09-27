#include <iostream>
#include <string>
#include <print>

using namespace std;

int main()
{
    
    //memory leak
    for (int i = 0; i < 5000000; i++) {
        string* Mleak = new string("No my memoryyyy I cannot believe this is happening what shall I ever do this is impossible.");
        string* leakNumberTwo = new string("Last attemp just to be extra");
        delete Mleak;
        delete leakNumberTwo;
    }
    print("Are you done yet? ");
    string confirmation;
    cin >> confirmation;

    return 0;
}
