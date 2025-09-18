#include "cycle.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int numberOfChanges;
    cout << "how many times did the light change?:";
    cin >> numberOfChanges;
    //calls cycleChanges in the class to take the value of numberOfChanges
    
    Lights::TrafficLights light;
    light.cycleChanges(numberOfChanges);

}
