#include "Car.h"
#include <iostream>

using namespace std;

//constructors
Car::Car() {
    numDoors = 4;
    isElectric = false;
}

Car::Car(string make, string model, int year, double mileage,
    int doors, bool electric)
    : Vehicle(make, model, year, mileage)
{
    setNumDoors(doors);
    setIsElectric(electric);
}
// Destructor
Car::~Car() {
    cout << "Destroying Car\n";
}

// Setters/Getters
void Car::setNumDoors(int doors) {
    if (doors > 0) {
        this->numDoors = doors;
    }
    else {
        cout << "Error: Number of doors must be positive.\n";
    }
}

int Car::getNumDoors() const {
    return numDoors;
}

void Car::setIsElectric(bool electric) {
    this->isElectric = electric;
}

bool Car::getIsElectric() const {
    return isElectric;
}

void Car::displayInfo() const {
    Vehicle::displayInfo();

    cout << "Type: Car | Doors: " << numDoors << " | Electric: ";
    if (isElectric) {
        cout << "Yes\n";
    }
    else {
        cout << "No\n";
    }
  
    cout << "Fuel Efficiency: " << getFuelEfficiency() << " km/l\n";
}

double Car::getFuelEfficiency() const {
    if (isElectric)
        return 0;  // electric
    else
        return 15; // gas
}