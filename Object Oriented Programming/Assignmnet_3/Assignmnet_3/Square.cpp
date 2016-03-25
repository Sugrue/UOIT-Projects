#include "Square.h"
	




Square::Square(){//constuctor 
	setA(1);
}
Square::Square(double side){//sets the sides of the square
	setA(side);
}
double Square::area(){//returns the area of the square
	return getA() * getA();
}
double Square::perimeter(){//returns the perimeter of the square
	return getA() *4;
}
