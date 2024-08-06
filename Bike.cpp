#include "Bike.h"


Bike::Bike(string make, string model, string reg, int age, int engineSize, int nooWheels)
	: Vehicle(make, model, reg, age), engineSize(engineSize), nooWheels(nooWheels)
{

}
Bike::~Bike()
{

}
void Bike::displayBasicsInformation() const
{
	cout << getReg() << "			" << "$" << getPrice() << "			" << "Bike" << endl;
}
 double  Bike::getPrice() const
{	
	 double price;
	 if (engineSize >= 50)
		 price = (1500 + ((engineSize + 50) / 100 * 100)) / 100.0;
	 else
		 price = (1500 + 100) / 100.0;
	if (price > 10)
		return price;
	else
		return 10;
}



ostream& operator<<(ostream& output, Bike* bike)
{
	Vehicle* vehicle = dynamic_cast<Vehicle*>(bike);
	output << vehicle;
	output << bike->engineSize;
	output << "\n";
	output << bike->nooWheels;
	output << "\n";
	output << "Bike\n";
	return output;
}