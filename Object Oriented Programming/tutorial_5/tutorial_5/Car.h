//car.h
#include <string>
#include <iostream>
using namespace std;

class Car{

//public members; accessible to all 
Car(string theModel, string theManufacturer, int theYear, int theMileage);


protected:
	void initCar(string theManufacturer, string theModel);
	void setAge(int theYear, int theMileage);
	void setValue(int val);
	void printKijiji();
//private members; only accessible within the class
private:
	int value;
	string manufacturer;
	string model;
	int year;
	int mileage;
};
