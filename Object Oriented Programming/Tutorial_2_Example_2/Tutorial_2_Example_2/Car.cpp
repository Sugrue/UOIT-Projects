//car.cpp
#include "car.h"

//sets the manufacturer and model of the car
//notice the "Car::" this means this function belongs to the "Car" class
void Car::initCar(string theManufacturer, string theModel){
	manufacturer = theManufacturer;
	model = theModel;
}
//sets the age of the car
void Car::setAge(int theYear, int theMileage){
	year = theYear;
	mileage = theMileage;
}

void Car::printKijiji(){
	cout<<"The "<<year<<" "<<manufacturer<<" "<<model<<" is one of the classics from this generation."<<endl;
	cout<<"With only "<<mileage<<" on the engine, this thing will go for another 10 years"<<endl;
	cout<<"Just a beauty"<<endl;
}
//sets the private member
void Car::setValue(int val){
	value = val;
}
