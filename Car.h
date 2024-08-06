#pragma once
#include "Vehicle.h"
#include <iostream>
using namespace std;
class Car :
    public Vehicle
{
public:
    Car(string, string, string, int, int, int);
    ~Car();
    int getNooDoors() { return nooDoors; }
    int getNooSeats() { return nooSeats; }
    friend ostream& operator<<(ostream& output, Car* vehicle);
    void displayBasicsInformation() const override;
protected:
    double getPrice() const override;

private:
    int nooDoors;
    int nooSeats;
};


ostream& operator<<(ostream& output, Car* vehicle);