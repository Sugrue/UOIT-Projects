#include "TwoDShape.h"

TwoDShape::TwoDShape(){
sideA = 1;
sideB = 1;
sideC = 0;

}
	void TwoDShape::setA(double a){
		sideA = a;
	}
	void TwoDShape::setB(double b){
		sideB = b;
	}
	void TwoDShape::setC(double c){
		sideC = c;
	}
	double TwoDShape::getA(){
		return sideA;
	}
	double TwoDShape::getB(){
		return sideB;
	}
	double TwoDShape::getC(){
		return sideC;
	}
	double TwoDShape::area(){
		return 0;
	}
	double TwoDShape::perimeter(){
		return 0;
	}