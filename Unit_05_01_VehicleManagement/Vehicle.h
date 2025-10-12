#pragma once
#include <string>
class Vehicle {
private:
	std::string make;
	std::string model;
	int year;
	double mileage;
	static int vehicleCount;
public:
	//constructors and destructors
	Vehicle();
	Vehicle(std::string carMake, std::string carModel, int y, double mile);
	virtual ~Vehicle();
	//setters
	void setMake(std::string make);
	void setModel(std::string model);
	void setYear(int year);
	void setMileage(double mileage);
	//getters
	std::string getMake() const;
	std::string getModel() const;
	int getYear() const;
	double getMileage() const;
	static int getVehicleCount();
	//virtuals
	virtual void displayInfo() const;
	virtual double getFuelEfficiency() const = 0;
};
