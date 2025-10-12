#include "Motorcycle.h"
#include <iostream>
using namespace std;

//constructors
Motorcycle::Motorcycle() {
    hasSidecar = false;
}


Motorcycle::Motorcycle(string make, string model, int year, double mileage,
    bool sidecar)
    : Vehicle(make, model, year, mileage)
{
    hasSidecar = sidecar;
}

// Destructor
Motorcycle::~Motorcycle() {
    cout << "Motorcycle object destroyed\n";
}

// Setters/Getters
void Motorcycle::setHasSidecar(bool sidecar) {
    hasSidecar = sidecar;
}

bool Motorcycle::getHasSidecar() const {
    return hasSidecar;
}

//override
void Motorcycle::displayInfo() const {
    Vehicle::displayInfo();
    cout << "Type: Motorcycle | Sidecar: ";
    if (hasSidecar) {
        cout << "Yes";
    }
    else {
        cout << "No";
    }
    cout << "\n";

    cout << "Fuel Efficiency: " << getFuelEfficiency() << " km/l\n";
}

double Motorcycle::getFuelEfficiency() const {
    // Sample value
    if (hasSidecar)
        return 25;  // slightly less efficient with a sidecar
    else
        return 30;  // high efficiency for normal motorcycles
}