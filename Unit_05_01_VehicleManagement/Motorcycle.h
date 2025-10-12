#pragma once
#pragma once
#include "Vehicle.h"
#include <string>

class Motorcycle : public Vehicle {
private:
    bool hasSidecar;

public:
    // Constructors
    Motorcycle();
    Motorcycle(std::string make, std::string model, int year, double mileage,
        bool sidecar);

    // Destructor
    ~Motorcycle();

    // Setters/Getters
    void setHasSidecar(bool sidecar);
    bool getHasSidecar() const;

    // Overrides
    void displayInfo() const override;
    double getFuelEfficiency() const override;
};