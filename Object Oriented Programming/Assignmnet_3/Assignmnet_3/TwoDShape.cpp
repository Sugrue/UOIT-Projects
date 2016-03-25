#include "TwoDShape.h"

TwoDShape::TwoDShape(){//constructor
	sideA = 1;
	sideB = 1;
	sideC = 0;
}
void TwoDShape::setA(double a){//sets sideA to the new value
	sideA = a;
}
void TwoDShape::setB(double b){//sets sideB to the new value
	sideB = b;
}
void TwoDShape::setC(double c){//sets sideC to the new value
	sideC = c;
}
double TwoDShape::getA(){//returns the value of sideA
	return sideA;
}
double TwoDShape::getB(){//returns the value of sideB
	return sideB;
}
double TwoDShape::getC(){//returns the value of sideC
	return sideC;
}
double TwoDShape::area(){//passed down the lower classes
	return 0;
}
double TwoDShape::perimeter(){//passed down to lower classes
	return 0;
}