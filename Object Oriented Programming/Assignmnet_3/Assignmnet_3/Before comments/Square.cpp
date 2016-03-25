#include "Square.h"
	




Square::Square(){
	setA(1);

}
Square::Square(double side){
	setA(side);

}
	double Square::area(){
		return getA() * getA();

	}
	double Square::perimeter(){
		return getA() *4;

	}
