#include "Vehicle.h"

Vehicle::Vehicle()
{

}
Vehicle::Vehicle(string make, string model, string reg, int age)
	:model(model), registrationNoo(reg), age(age)
{
	
	makeLength = make.length();
	this->make = (char*)malloc(makeLength * sizeof(char) + 1);
	for (int i = 0; i < makeLength; i++)
		this->make[i] = make.at(i);	
	this->make[makeLength] = '\0';

	//read the customers from history and store them in array object 
	int count = 0;
	ifstream file(registrationNoo);
	if (file.is_open())
	{
		string line;

		while (!file.eof())
		{
			count++;
			getline(file, line);
		}
		file.clear();
		file.seekg(0, ios::beg);

		nooCustomers = count / 7;
		if (nooCustomers != 0)
		{
			customers = (Customer**)malloc(sizeof(Customer) * nooCustomers);
			int count1 = 0;
			string date1, date2, name, address, contactNumber, nooDays, cost;
			int customerRead = 1;
			while (!file.eof())
			{
				count1++;
				if (count1 == 1 + customerRead * 7)
				{
					getline(file, date1);
				}

				if (count1 == 2 + customerRead * 7)
				{
					getline(file, date2);
				}

				if (count1 == 3 + customerRead * 7)
				{
					getline(file, name);
				}

				if (count1 == 4 + customerRead * 7)
				{
					getline(file, address);
				}
				if (count1 == 5 + customerRead * 7)
				{
					getline(file, contactNumber);
				}

				if (count1 == 6 + customerRead * 7)
				{
					getline(file, nooDays);
				}

				if (count1 == 7 + customerRead * 7)
				{
					getline(file, cost);
					int days = atoi(nooDays.c_str());
					double dCost = atof(cost.c_str());
					customers[customerRead - 1] = new Customer(date1, date2, name, address, contactNumber, days, dCost);
					customerRead++;

				}
			}

			file.close();
		}
	}
	
}
Vehicle::~Vehicle()
{
	//clean memory 
	for (int i = 0; i < nooCustomers; i++)
		delete customers[i];
	delete[] customers;
	customers = nullptr;
	delete[] make;
}

void Vehicle::deleteVehicle()
{
	//delete the vehicle history file
	const char* str = registrationNoo.c_str();
	remove(str);
}

void Vehicle::displayCustomers() const
{

	if (nooCustomers > 0)
	{
		int option = 0;
		int noo = 1;
		while (option != 9)
		{
			if (noo <= nooCustomers)
			{

				cout << "Rental:            " << noo << " of " << nooCustomers << endl;
				customers[noo - 1]->displayCustomer();
				if (noo != 1)
					cout << "1) View the previous record" << endl;
				if (noo != nooCustomers)
					cout << "2) View the next record" << endl;

				cout << "9) Return to vehicle information screen" << endl;

				cin >> option;
				if (option == 1 && noo > 1)
					noo--;
				if (option == 2 && noo < nooCustomers)
					noo++;

			}

		}
	}

	else
		cout << "This vehicle has no record" << endl;
}

void Vehicle::addCustomer() 
{
	//resize customer array object
	nooCustomers++;
	Customer* customer = new Customer(getPrice());
	customers = (Customer**)realloc(customers, sizeof(Customer) * nooCustomers);
	customers[nooCustomers - 1] = customer;
}
void Vehicle::saveCustomer()
{
	//write the customers to history file
	ofstream ox(registrationNoo);
	for (int i = 0; i < nooCustomers; i++)
		ox << customers[i];
}
void Vehicle::displaySummary() const
{
	cout << registrationNoo << ": " << getMake() << " " << model << endl;
	cout << "----------------" << endl;
	int totalNooDaysRented = 0;
	double incomeGenerated = 0;
	for (int i = 0; i < nooCustomers; i++)
		totalNooDaysRented = totalNooDaysRented + customers[i]->getNooDays();
	for (int i = 0; i < nooCustomers; i++)
		incomeGenerated = incomeGenerated + customers[i]->getCost();
	cout << "Cost Per Day:          $" << getPrice() << endl;
	cout << "Cost Per Day:          $" << incomeGenerated << endl;
	cout << "Total Days Rented:      " << totalNooDaysRented << endl;
}
void Vehicle::displayAdvancedInformation() const
{
	cout << registrationNoo << "					" << "$" << getPrice() << "				" << getMake() << "			" << model << endl;
}

ostream& operator<<(ostream& output, Vehicle* vehicle)
{
	string make1 = "";
	for (int i = 0; i < vehicle->makeLength; i++)
		make1 = make1 + vehicle->make[i];
	output << vehicle->registrationNoo;
	output << "\n";
	output << vehicle->getMake();
	output << "\n";
	output << vehicle->model;
	output << "\n";
	output << vehicle->age;
	output << "\n";
	return output;
}

string Vehicle::getMake() const
{
	string make1 = "";
	for (int i = 0; i < makeLength; i++)
		make1 = make1 + make[i];
	return make1;
}