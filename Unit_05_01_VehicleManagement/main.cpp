#include <iostream>
#include "Car.h"
#include "Truck.h"
#include "Motorcycle.h"
#include "Fleet.h"
#include <iomanip>

using namespace std;

int main() {
    cout << "Vehicle Management System\n";
    cout << "--------------------------\n\n";

    Fleet myFleet;

    Vehicle* car1 = new Car("Toyota", "Corolla", 2020, 20000, 4, false);
    Vehicle* truck1 = new Truck("Volvo", "FH16", 2018, 80000, 18);
    Vehicle* moto1 = new Motorcycle("Honda", "CBR600", 2021, 5000, false);
    Vehicle* car2 = new Car("Tesla", "Model 3", 2022, 15000, 4, true);

    myFleet.addVehicle(car1);
    myFleet.addVehicle(truck1);
    myFleet.addVehicle(moto1);
    myFleet.addVehicle(car2);

    myFleet.displayAllVehicles();

    cout << "Total vehicles: " << Vehicle::getVehicleCount() << "\n";
    cout << fixed << setprecision(2);
    cout << "Average fuel efficiency: " << myFleet.getAverageEfficiency() << " km/l\n";
    cout << "\nProgram ending... destructors will now be called automatically.\n";

    return 0;
}