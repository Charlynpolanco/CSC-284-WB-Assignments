#pragma once
#include "Vehicle.h"
#include <string>

class Truck : public Vehicle {
private:
    double loadCapacity; // in tons

public:
    // Constructors
    Truck();
    Truck(std::string make, std::string model, int year, double mileage,
        double capacity);

    // Destructor
    ~Truck();

    // Setters/Getters
    void setLoadCapacity(double loadCapacity);
    double getLoadCapacity() const;

    // Overrides
    void displayInfo() const override;
    double getFuelEfficiency() const override;
};