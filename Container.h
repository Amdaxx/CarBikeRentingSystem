#pragma once
#include <iterator>
#include <algorithm>
#include "Vehicle.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Car.h"
#include "Bike.h"
#include "Customer.h"
#include <vector>

class Container
{
public:
	Container();
	~Container();

	void createVehicle();
	void displayVehicle();
	void removeVehicle();
	void searchForCar();
	void searchForBike();
	void sortBy(int);
	
protected:
	//help function when user slect a vehicle
	void selectVehicle(Vehicle*);

	//help function to search for a specefic registration number either bike/car
	template<typename T>
	void searchRegistration(vector<T*>&, string, string);

	//help function to search for specefic car by its propreties
	template<typename S>
	void searchForCarBy(vector<Car*>&, string, S);

	//help function to search for specefic bike by its propreties
	template<typename K>
	void searchForBikeBy(vector<Bike*>&, string, K);
private:
	vector<Vehicle*> vehicles;
};
