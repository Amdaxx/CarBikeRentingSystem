#pragma once
#include "Vehicle.h"
class Bike :
    public Vehicle
{
public:

    Bike(string, string, string, int, int, int);
    ~Bike();
    int getEngineSize() { return engineSize; }
    int getNooWheels() { return nooWheels; }
    friend ostream& operator<<(ostream& output, Bike* bike);
    void displayBasicsInformation() const override;

protected:
    double getPrice() const override;
private:
    double engineSize;
    int nooWheels;
};

ostream& operator<<(ostream& output, Bike* bike);