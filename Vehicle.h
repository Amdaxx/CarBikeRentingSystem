#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Customer.h"

using namespace std;
#pragma once
class Vehicle
{
public:
	Vehicle();
	Vehicle(string, string, string, int);
	~Vehicle();

	void deleteVehicle();

	string getReg() const { return registrationNoo; }
	virtual double getPrice() const = 0;
	virtual void displayBasicsInformation() const = 0;
	void displayAdvancedInformation() const;
	void displayReg() const { cout << registrationNoo << endl; }
	void displaySummary() const;
	void displayCustomers() const;
	void addCustomer();
	void saveCustomer();

	friend ostream& operator<<(ostream& output, Vehicle* vehicle);
protected:
	int getAge() const { return age; }
	string getMake() const;
private:
	char* make;
	int makeLength;
	string model;
	string registrationNoo;
	int age;
	int nooCustomers;
	Customer** customers;

};

ostream& operator<<(ostream& output, Vehicle* vehicle);

