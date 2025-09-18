#include "cycle.h"
#include <iostream>
#include <vector>

using namespace std;

//Cycles through the content of the traficLights vector by an amount given by the user

int main() {
    int numberOfChanges;
    cout << "how many times did the light change?:";
    cin >> numberOfChanges;
    //calls trafficLightCycler and passes the numberofChanges for the lights to cycle through.
    
    Lights::TrafficLights light;
    light.cycleChanges(numberOfChanges);
}