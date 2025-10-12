#include "Vehicle.h"
#include <iostream>
#include <iomanip>

using namespace std;

int Vehicle::vehicleCount = 0;
//constructors

Vehicle::Vehicle() {
	make = "Unknown";
	model = "Unknown";
	year = 0;
	mileage = 0.0;
	vehicleCount++;
}
Vehicle::Vehicle(string carMake, string carModel, int yr, double mile) 
	{
	setMake(carMake);
	setModel(carModel);
	setYear(yr);
	setMileage(mile);
	vehicleCount++;
}
Vehicle::~Vehicle() {
}

void Vehicle::setMake(string make) {
	if (!make.empty()) {  // validate the impute
		this->make = make;
	}
	else {
		std::cout << "Error: Make cannot be empty/blank.\n";
	}
}
void Vehicle::setModel(string model) {
	if (!model.empty()) { //validate input
		this->model = model;
	}
	else {
		cout << "Error: Model cannot be left empty/blank.";
	}
}
void Vehicle::setYear(int year) {
	if (year >= 1886) { //validate input
		this->year = year;
	}
	else {
		cout << "Error: Car had not been invented yet.\n";
	}
}
void Vehicle::setMileage(double mileage) {
	if (mileage >= 0) { //validate input
		this->mileage = mileage;
	}
	else {
		cout << "Error: mileage cannot be below zero(0)\n";
	}
}

//getters
string Vehicle::getMake() const {
	return make;
}
string Vehicle::getModel() const {
	return model;
}
int Vehicle::getYear() const {
	return year;
}
double Vehicle::getMileage() const {
	return mileage;
}
 int Vehicle::getVehicleCount() {
	return vehicleCount; 
}
//virtuals

void Vehicle::displayInfo() const {
	cout << year << " " << make << " " << model << " | " 
		<< "Mileage: " << fixed << setprecision(0) << mileage << " km\n";
}
