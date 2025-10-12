#pragma once
#include <vector>
#include "Vehicle.h"

class Fleet {
private:
    std::vector<Vehicle*> vehicles; 

public:
 
    Fleet();

    
    ~Fleet();

    
    void addVehicle(Vehicle* v);

    void displayAllVehicles() const;

    double getAverageEfficiency() const;
};