#include "Car.h";

void Car::initCar(string  myManufacturer, string myModel) {
	value = rand() % (30000-100)+ 100;
	manufacturer = myManufacturer;
	model = myModel;
}
void Car::setAge(int myYear, int myMileage) {
	year = myYear;
	mileage = myMileage;

}


void Car::createKijijiAd(){
	cout<<"I'm selling a classic "<<year<<" "<<manufacturer<<" "
		<<model<<". This monster only has "<<mileage<<"kms on the monter."
		<<"At only $"<<value<<" It's a steal"<<endl;
}



