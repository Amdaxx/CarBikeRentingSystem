#include "Customer.h"

Customer::Customer()
{

}
Customer::Customer(double cost)

{
	cin.clear();
	cin.ignore();
	cout << "Please enter your name" << endl;
	getline(cin, name);
	cout << "Please enter your address" << endl;
	getline(cin, address);
	cout << "Please enter your contact number" << endl;
	getline(cin, contactNumber);

	readInput(nooDays, "Please enter the number of days you want to rent this vehicle");
	this->cost = cost;

	//generate date:
	//source used: https://cplusplus.com/reference/ctime/
	char TIME[11];
	time_t T1 = time(nullptr);
	struct tm T2;
	if (localtime_s(&T2, &T1) == 0)
		strftime(TIME, sizeof(TIME), "%F", &T2);

	int days = TIME[8] - '0';
	days = days * 10;
	days = days + TIME[9] - '0';
	int months = TIME[5] - '0';
	months = months * 10;
	months = months + TIME[6] - '0';
	int years = (TIME[0] - '0') * 1000;
	years = years + ((TIME[1] - '0') * 100);
	years = years + ((TIME[2] - '0') * 10);
	years = years + (TIME[3] - '0');
	date1 = to_string(years) + "-" + to_string(months) + "-" + to_string(days);
	if ((days + nooDays) > 30)
	{
		days = 30 - days;
		if (months == 12)
		{
			years++;
			months = 1;
		}

	}
	else
		days = days + nooDays;
	date2 = to_string(years) + "-" + to_string(months) + "-" + to_string(days);
}

Customer::Customer(string date1, string date2, string name, string address, string contactNumber, int nooDays, double cost)
	:date1(date1), date2(date2), name(name), address(address), contactNumber(contactNumber),
	nooDays(nooDays), cost(cost)
{

}
Customer::~Customer()
{

}


void Customer::displayCustomer()
{

	cout << "Date From:         " << date1 << endl;
	cout << "Date to            " << date2 << endl;
	cout << "Rental Days        " << nooDays << endl;
	cout << "Total Cost         " << cost << endl;
	cout << "Customer Name:     " << name << endl;
	cout << "Customer Address:  " << address << endl;
	cout << "Customer Number:   " << contactNumber << "\n" << "\n" << endl;
}

ostream& operator<<(ostream& output, Customer* customer)
{
	output << customer->date1 + "\n";
	output << customer->date2 + "\n";
	output << customer->name + "\n";
	output << customer->address + "\n";
	output << customer->contactNumber + "\n";
	output << customer->nooDays;
	output << "\n";
	output << customer->cost;
	output << "\n";

	return output;
}