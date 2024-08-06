#include <iostream>
#include <crtdbg.h>
#include "Vehicle.h"
#include "Bike.h"
#include "Car.h"
#include "Container.h"
#include "Customer.h"

using namespace std;
void create(shared_ptr<Container> container) { container->createVehicle(); }
void remove(shared_ptr<Container> container) { container->removeVehicle(); }
void searchCar(shared_ptr<Container> container) { container->searchForCar(); }
void searchBike(shared_ptr<Container> container) { container->searchForBike(); }
void sortPrice(shared_ptr<Container> container) { container->sortBy(1); }
void sortReg(shared_ptr<Container> container) { container->sortBy(2); }

#ifdef _DEBUG

int main()
{
	//_CrtSetBreakAlloc(87);
	_onexit(_CrtDumpMemoryLeaks);
#endif

	int option = 0;
	shared_ptr<Container> container(new Container());
	while (option != 9)
	{
		cout << "Vehicle Rental System" << endl;
		cout << "---------------------" << endl;
		container->displayVehicle();
		cout << "1) Add vehicle " << endl;
		cout << "2) Remove vehicle" << endl;
		cout << "3) Search for car" << endl;
		cout << "4) Search for bike" << endl;
		cout << "5) Sort vehicles by registration number" << endl;
		cout << "6) Sort by cost per day" << endl;
		cout << "9) Exit" << endl;
		readInput(option, "");
		if (option >= 1 && option <= 6)
		{
			void(*options[6])(shared_ptr<Container>) = { &create, &remove, &searchCar, &searchBike, &sortPrice, &sortReg };
			options[option - 1](container);
		}

	}

}