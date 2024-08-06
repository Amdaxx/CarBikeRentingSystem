#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;
class Customer
{
public:
	Customer();
	Customer(double);
	Customer(string, string, string, string, string, int, double);
	~Customer();
	int getNooDays() { return nooDays; }
	double getCost() { return cost; }
	void displayCustomer();
	friend ostream& operator<<(ostream& output, Customer* customer);	

private:
	string name;
	string address;
	string contactNumber;
	int nooDays;
	double cost;
	string date1;
	string date2;
};

ostream& operator<<(ostream& output, Customer* customer);


//function that read any type of input from user to prevent from crash
//source used: https://cplusplus.com/reference/ios/ios/fail/
template<typename T>
void readInput(T& value, string message)
{
    bool again = true;
    while (again)
    {
        cin.exceptions(istream::failbit | istream::badbit);
        try
        {
            cout <<message<< endl;
            cin >> value;
            if (!cin.fail())
                again = false;
        }
        catch (istream::failure) {
            cout << "failed to read value" << std::endl;
            cin.clear();
            cin.ignore();
        }
    }
}