#include <string>
#include <iostream>

using namespace std;

class Car {

public:
	string manufacturer;
	string model;
	int year;
	int mileage;

	void initCar(string myManufacturer, string myModel);
	void setAge(int myYear, int myMileage);
	void createKijijiAd();

private:
	int value;


}