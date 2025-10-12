#include "Fleet.h"
#include <iostream>
using namespace std;

// Constructor
Fleet::Fleet() {
}

Fleet::~Fleet() {
   
    for (size_t i = 0; i < vehicles.size(); ++i) {
        delete vehicles[i];
    }
    vehicles.clear();
    cout << "Fleet destroyed, all vehicles deleted.\n";
}


void Fleet::addVehicle(Vehicle* v) {
    vehicles.push_back(v);
}


void Fleet::displayAllVehicles() const {
    cout << "--- Fleet Vehicles ---\n";
    for (size_t i = 0; i < vehicles.size(); ++i) {
        vehicles[i]->displayInfo();
        cout << "\n";
    }
}


double Fleet::getAverageEfficiency() const {
    if (vehicles.empty()) { 
        return 0.0; 
    }

    double sum = 0.0;
    for (size_t i = 0; i < vehicles.size(); ++i) {
        sum += vehicles[i]->getFuelEfficiency();
    }

    return sum / vehicles.size();
}