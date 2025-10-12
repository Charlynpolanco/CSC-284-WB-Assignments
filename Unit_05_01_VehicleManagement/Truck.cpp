#include "Truck.h"
#include <iostream>
using namespace std;

//constructors
Truck::Truck() {
    loadCapacity = 5.0; 
}


Truck::Truck(string make, string model, int year, double mileage,
    double capacity)
    : Vehicle(make, model, year, mileage)
{
    loadCapacity = capacity;
}

// Destructor
Truck::~Truck() {
    cout << "Truck object destroyed\n";
}

// Setters/Getters
void Truck::setLoadCapacity(double loadCapacity) {
    if (loadCapacity >= 0) {
        this->loadCapacity = loadCapacity;
    }
    else {
        cout << "Error: Load capacity must be 0 or bigger.\n";
    }
}

double Truck::getLoadCapacity() const {
    return loadCapacity;
}

//override
void Truck::displayInfo() const {
    Vehicle::displayInfo();
    cout << "Type: Truck | Load Capacity: " << loadCapacity << " tons\n";
    cout << "Fuel Efficiency: " << getFuelEfficiency() << " km/l\n";
}


double Truck::getFuelEfficiency() const {
    // Sample value for trucks (less efficient)
    return 8;
}