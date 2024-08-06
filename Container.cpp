#include "Container.h"

Container::Container()
{
	//count number of vehicles
	int count = 0;
	ifstream input("vehicles.txt");
	if (input.is_open())
	{

		string line;

		while (!input.eof())
		{
			count++;
			getline(input, line);


		}
		input.clear();
		input.seekg(0, ios::beg);

		int nooVehicles = count / 7;
		int count2 = 0;
		int vehicleRead = 1;
		string reg, make, model, type, age, prop1, prop2;
		//each 7 lines is a information about one vehicle so we will be moving by 7 lines for each vehicle
		while (!input.eof())
		{
			count2++;
			if (count2 == 1 + vehicleRead * 7)
			{
				getline(input, reg);
			}

			if (count2 == 2 + vehicleRead * 7)
			{
				getline(input, make);
			}

			if (count2 == 3 + vehicleRead * 7)
			{
				getline(input, model);
			}

			if (count2 == 4 + vehicleRead * 7)
			{
				getline(input, age);
			}
			if (count2 == 5 + vehicleRead * 7)
			{
				getline(input, prop1);
			}

			if (count2 == 6 + vehicleRead * 7)
			{
				getline(input, prop2);
			}

			if (count2 == 7 + vehicleRead * 7)
			{
				getline(input, type);
				int intage = atoi(age.c_str());
				//push the vehicle to the vector when we hit the seventh line
				if (type == "Car")
				{
					int nooDoors = atoi(prop1.c_str());
					int nooSeats = atoi(prop2.c_str());
					vehicles.push_back(new Car(make, model, reg, intage, nooDoors, nooSeats));
				}

				else
				{
					int engineSize = atoi(prop1.c_str());
					int nooWheels = atoi(prop2.c_str());
					vehicles.push_back(new Bike(make, model, reg, intage, engineSize, nooWheels));
				}
				vehicleRead++;
			}
		}
	}
}
Container::~Container()
{
	//write the vehicles back to file
	ofstream os("vehicles.txt");
	if (!vehicles.empty())
	{
		for (int j = 0; j < vehicles.size(); j++)
		{
			
			string type = typeid(*vehicles.at(j)).name();
			if (type == "class Car")
			{
				Car* car = dynamic_cast<Car*>(vehicles.at(j));
				os << car;
			}
			if (type == "class Bike")
			{
				Bike* bike = dynamic_cast<Bike*>(vehicles.at(j));
				os << bike;
			}
			vehicles.at(j)->saveCustomer();
		}

	}
	else
		os << "";
	os.close();

	//clean memmory 
	for (int k = 0; k < vehicles.size(); k++)
	{
		delete vehicles.at(k);
	}

}

void Container::displayVehicle()
{
	vector<Vehicle*>::const_iterator cit(vehicles.begin());
	while (cit != vehicles.end())
	{
		(*cit)->displayBasicsInformation();
		cit++;
	}
}

bool sortOnPrice(const Vehicle* lhs, const Vehicle* rhs)
{
	return lhs->getPrice() < rhs->getPrice();
}
bool sortOnReg(const Vehicle* lhs, const Vehicle* rhs)
{
	return lhs->getReg() < rhs->getReg();
}


void Container::sortBy(int a)
{
	//using smart function to sort vehicles
	bool(*options[2])(const Vehicle*, const Vehicle*) = {sortOnReg, sortOnPrice };
	sort(vehicles.begin(), vehicles.end(), options[a - 1]);
	
	cout << "Registration Number             Price            Type" << endl;
	for (int i = 0; i < vehicles.size(); i++)
	{
		cout << i + 1 << ")";
		vehicles.at(i)->displayBasicsInformation();
	}
	cout << "0) Back to menu" << endl;
	int select;

	readInput(select, "Please select a vehicle");
	if (select>0 && select<vehicles.size()+1)
		selectVehicle(vehicles.at(select - 1));
}

template<typename T>
void Container::searchRegistration(vector<T*>& vec, string type, string registration)
{	
	transform(registration.begin(), registration.end(), registration.begin(), ::toupper);
	//search for registration number and type of vehicle using lambda function and push the vehicles to search function vector
	vector<Vehicle*>::iterator it = find_if(vehicles.begin(), vehicles.end(), [type, registration](Vehicle* vehicle)
		{ 
			return typeid(*vehicle).name() == ("class " + type ) 
				&& registration==vehicle->getReg();
		});
	
	while (it != vehicles.end())
	{
		T* veh = dynamic_cast<T*>(*it);
		vec.push_back(veh);
		it = find_if(it + 1 , vehicles.end(), [type, registration](Vehicle* vehicle)
			{
				return typeid(*vehicle).name() == ("class " + type)
					&& registration == vehicle->getReg();
			});
	}
}
template<typename S>
void Container::searchForCarBy(vector<Car*>& vec, string proprerty, S prop)
{
	//store all vehicles of type car in a vector using lambda function
	vector<Car*> cars;
	vector<Vehicle*>::iterator it = find_if(vehicles.begin(), vehicles.end(), [](Vehicle* vehicle)
		{ 
			string type = typeid(*vehicle).name();
			return type == "class Car"; 
		});

	while (it != vehicles.end())
	{
		Car* veh = dynamic_cast<Car*>(*it);
		cars.push_back(veh);
		it = find_if(it + 1 , vehicles.end(), [](Vehicle* vehicle)
			{
				string type = typeid(*vehicle).name();
				return type == "class Car";
			});
	}

	if (!cars.empty())
	{
		//search for specefic cars and store in search car function vector
		vector<Car*>::iterator cit = find_if(cars.begin(), cars.end(), [proprerty, prop](Car* car)
			{
				if (proprerty == "Number of doors")
				{
					return car->getNooDoors() == prop;
				}
				else
					return car->getNooSeats() == prop;
			});

		while (cit != cars.end())
		{
			vec.push_back(*cit);
			cit = find_if(cit + 1, cars.end(), [proprerty, prop](Car* car)
				{
					if (proprerty == "Number of doors")
					{
						return car->getNooDoors() == prop;
					}
					else
						return car->getNooSeats() == prop;
				});
		}
	}
	
}

template<typename K>
void Container::searchForBikeBy(vector<Bike*>& vec, string proprerty, K prop)
{
	//store all bikes to a vector using lambda function
	vector<Bike*> bikes;
	vector<Vehicle*>::iterator it = find_if(vehicles.begin(), vehicles.end(), [](Vehicle* vehicle)
		{
			string type = typeid(*vehicle).name();
			return type == "class Bike";
		});

	while (it != vehicles.end())
	{
		Bike* veh = dynamic_cast<Bike*>(*it);
		bikes.push_back(veh);
		it = find_if(it + 1, vehicles.end(), [](Vehicle* vehicle)
			{
				string type = typeid(*vehicle).name();
				return type == "class Bike";
			});
	}

	if (!bikes.empty())
	{
		//search for bikes with specefic characteristics and store them in search bike function vector
		vector<Bike*>::iterator cit = find_if(bikes.begin(), bikes.end(), [proprerty, prop](Bike* bike)
			{
				if (proprerty == "Engine size")
				{
					return bike->getEngineSize() == prop;
				}
				else
					return bike->getNooWheels() == prop;
			});

		while (cit != bikes.end())
		{
			vec.push_back(*cit);
			cit = find_if(cit + 1 , bikes.end(), [proprerty, prop](Bike* bike)
				{
					if (proprerty == "Engine size")
					{
						return bike->getEngineSize() == prop;
					}
					else
						return bike->getNooWheels() == prop;
				});
		}
	}
	
}

void Container::searchForBike()
{
	vector<Bike*> bikesFound;

	cout << "1) Search by registration Number" << endl;
	cout << "2) Search by engine size" << endl;
	cout << "3) Search by number of wheels" << endl;
	int option;
	readInput(option, "");
	
	//call help functions with user inputs as parameters
	switch (option)
	{
	case 1:
	{
		cin.clear();
		cin.ignore();
		string reg;
		cout << "Please enter the registration number" << endl;
		getline(cin, reg);
		searchRegistration(bikesFound, "Bike", reg);
		break;
	}
		
	case 2:
	{
		double engineSize;
		readInput(engineSize, "Please enter the engine size");
		searchForBikeBy(bikesFound, "Engine size", engineSize);
		break;
	}
	case 3:
	{
		int nooWheels = 0;
		while (nooWheels != 1 && nooWheels != 2)
		{
			cout << "Do you want to search for a two or three-wheeler bike" << endl;
			cout << "1) Two-Wheeler" << endl;
			cout << "2) Three-Wheeler" << endl;
			readInput(nooWheels, "");
		}
		searchForBikeBy(bikesFound, "number of wheels", (nooWheels+1));
		break;
	}
	default: cout << "Please select a value in range of the proposed options \n\n" << endl;
		break;
	}

	if (option >= 1 && option <= 3)
	{
		//display the bikes that match the user search
		if (!bikesFound.empty())
		{
			cout << "Registration Number" << "			" << "Cost Per Day" << "			" << "Make" << "			" << "Model" << endl;
			for (int i = 0; i < bikesFound.size(); i++)
			{
				cout << i + 1 << ")";
				bikesFound.at(i)->displayAdvancedInformation();
			}
			cout << "0) Back to menu" << endl;
			int select;
			readInput(select, "please select a bike");
			if (select != 0 && select <= bikesFound.size() && select >= 1)
				selectVehicle(bikesFound.at(select - 1));
		}
		else
			cout << "There is no bike that matches your specefication \n" << endl;
	}
	

}

void Container::searchForCar()
{
	vector<Car*> carsFound;
	int option;
	cout << "1) Search by registration Number" << endl;
	cout << "2) Search by number of doors" << endl;
	cout << "3) Search by number of seats" << endl;
	readInput(option, "");
	
	//call the help function depending on user input
	switch (option)
	{
	case 1:
	{
		cin.clear();
		cin.ignore();
		string reg;
		cout << "Please enter the registration number" << endl;
		getline(cin, reg);
		searchRegistration(carsFound, "Car", reg);

		break;
	}
	case 2:
	{
		int nooDoors;
		readInput(nooDoors, "Please enter the number of doors");
		searchForCarBy(carsFound, "Number of doors", nooDoors);
		break;
	}
	case 3:
	{
		int nooSeats;
		readInput(nooSeats, "Please enter number of seats");
		searchForCarBy(carsFound, "Number of seats", nooSeats);
		break;
	}
	default: cout << "Please select a value in range of the proposed options \n\n" << endl;
		break;
	}

	if (option >= 1 && option <= 3)
	{
		//display the cars that match the user search
		if (!carsFound.empty())
		{
			cout << "Registration Number" << "			" << "Cost Per Day" << "			" << "Make" << "			" << "Model" << endl;
			for (int i = 0; i < carsFound.size(); i++)
			{
				cout << i + 1 << ")";
				carsFound.at(i)->displayAdvancedInformation();
			}
			cout << "0) Back to menu" << endl;
			int select;
			readInput(select, "Please select a car");
			if (select > 0 && select < carsFound.size() + 1)
				selectVehicle(carsFound.at(select - 1));
		}
		else
			cout << "There is no car that matches your specefication" << endl;
	}

}

void Container::removeVehicle()
{
	int option = 0;
	int number = 0;
	vector<Vehicle*>::const_iterator cit(vehicles.begin());
	while (cit != vehicles.end())
	{
		number++;
		cout << number << ")";
		(*cit)->displayAdvancedInformation();
		cit++;
	}
	cout << "0) return to menu" << endl;
	cout << "Please select the vehicle that you want to remove" << endl;

	readInput(option, "");
	if (option >= 1 && option <= number) {
		//delete the vehicle history file
		vehicles.at(option - 1)->deleteVehicle();
		//clean delete object to avoid memory leak
		delete vehicles.at(option - 1);
		//delete the vehicle from vector
		vehicles.erase(vehicles.begin() + option - 1);
		
	}

}

void Container::selectVehicle(Vehicle* vehicle)
{
	vehicle->displaySummary();
	int option;
	cout << "1) View this vehicle records" << endl;
	cout << "2) Add a new record" << endl;
	cout << "9) Back to menu" << endl;;
	readInput(option, "");
	switch (option)
	{
	case 1:
		vehicle->displayCustomers();
		break;
		
	case 2:
		vehicle->addCustomer();
		break;

	default:
		cout << "Wrong input" << endl;
	}

}

void Container::createVehicle()
{
	string make, model, registrationNoo;
	int age, vehType;
	bool again = true;
	cin.clear();
	cin.ignore();
	cout << "Please enter the registratio number of the vehicle" << endl;
	while (again)
	{
		getline(cin, registrationNoo);
		bool verify = false;
		transform(registrationNoo.begin(), registrationNoo.end(), registrationNoo.begin(), ::toupper);
		for (int i = 0; i < vehicles.size(); i++)
		{
			if (vehicles.at(i)->getReg() == registrationNoo)
				verify = true;

		}
		if (verify == true)
			cout << "This registration number already exists please enter another one" << endl;
		if (!cin.fail() && verify == false)
			again = false;
	}
	cout << "Please enter the make of your vehicle" << endl;
	getline(cin, make);
	cout << "Please enter the model of your vehicle" << endl;
	getline(cin, model);


	cout << "What type of vehicle do you want to add" << endl;
	cout << "1) Car" << endl;
	cout << "2) Bike" << endl;
	readInput(vehType, "");


	readInput(age, "Please enter the age of the vehicle");

	if (vehType == 1)
	{
		int nooDoors, nooSeats;
		readInput(nooDoors, "Please enter the number of doors");
		readInput(nooSeats, "Please enter the number of seats");
		vehicles.push_back(new Car(make, model, registrationNoo, age, nooDoors, nooSeats));
	}
	else
	{
		int engineSize;
		int nooWheels = 0;
		readInput(engineSize, "Please enter the engine size");
		while (nooWheels != 1 && nooWheels != 2)
		{
			cout << "Is it a two or three-wheeler bike" << endl;
			cout << "1) Two-Wheeler" << endl;
			cout << "2) Three-Wheeler" << endl;
			readInput(nooWheels, "");
		}
			
		vehicles.push_back(new Bike(make, model, registrationNoo, age, engineSize, (nooWheels + 1)));
	}
}