#include "Triangle.h"



Triangle::Triangle(){
	setA(1);
	setB(1);
	setC(1);
}
Triangle::Triangle(double sideA, double sideB, double sideC) {
	setA(sideA);
	setB(sideB);
	setC(sideC);
}
double Triangle::area(){
	double s = perimeter()/2;
	return sqrt(s*(s-getA())*(s-getB())*(s-getC()));
	return 0;
}
double Triangle::perimeter(){
	return getA() + getB() + getC();
}
