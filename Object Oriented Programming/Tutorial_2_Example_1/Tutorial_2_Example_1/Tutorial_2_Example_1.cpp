#include <iostream>;
#include <string>;
#include "Car.h";

using namespace std;


int main() {
	string manufacturer;
	string model;

	cout<<"Please enter a manufacturer"<<endl;

	getline(cin,manufacturer);
	cout<<"What is the model?"<<endl;
	getline(cin,model);

	Car myCar;
	myCar.initCar(manufacturer, model);

	cout<<"What year is it?"<<endl;
	cin>>myCar.year;

	cout<<"What's the milage?"<<endl;
	cin>>myCar.mileage;

	myCar.createKijijiAd();

	system("pause");
	return 0;
}