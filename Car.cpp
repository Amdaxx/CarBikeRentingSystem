#include "Car.h"
using namespace std;

Car::Car(string make, string model, string reg, int age, int nooDoors, int nooSeats)
	: Vehicle(make, model, reg, age), nooDoors(nooDoors), nooSeats(nooSeats)
{

}
Car::~Car()
{

}

 double  Car::getPrice() const
{
	double price = (2500 - ((double)getAge() * 150) - ((double)nooDoors * 200)) / 100;
	if (price > 10)
		return price;
	else
		return 10;
}
 void Car::displayBasicsInformation() const
 {
	 cout << getReg() << "			" << "$" << getPrice() << "			" << "Car" << endl;
	 
 }

ostream& operator<<(ostream& output, Car* car)
{
	Vehicle* vehicle = dynamic_cast<Vehicle*>(car);
	output << vehicle;
	output << car->nooDoors;
	output << "\n";
	output << car->nooSeats;
	output << "\n";
	output << "Car";
	output << "\n";
	return output;
}