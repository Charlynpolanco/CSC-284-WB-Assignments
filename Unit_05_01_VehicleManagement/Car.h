#pragma once
#include "Vehicle.h"
class Car : public Vehicle { 
private:
    int numDoors;
    bool isElectric;

public:
    // Constructors
    Car();  // default constructor
    Car(std::string make, std::string model, int year, double mileage,
        int doors, bool electric);

    // Destructor
    ~Car();

    // Setters/Getters
    void setNumDoors(int doors);
    int getNumDoors() const;

    void setIsElectric(bool electric);
    bool getIsElectric() const;

    // Overrides
    void displayInfo() const override;
    double getFuelEfficiency() const override;
};