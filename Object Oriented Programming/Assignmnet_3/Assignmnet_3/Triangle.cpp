#include "Triangle.h"



Triangle::Triangle(){//constructor
	setA(1);
	setB(1);
	setC(1);
}
Triangle::Triangle(double sideA, double sideB, double sideC) {//sets the sides of the triangle
	setA(sideA);
	setB(sideB);
	setC(sideC);
}
bool Triangle::isTriangle() {
	if ((getA() + getB() > getC()) && (getA() + getC() > getB()) && (getB() + getC() > getA()))
		return true;
	else
		return false;

}
double Triangle::area(){//determines the area
	double s = perimeter()/2;
	return sqrt(s*(s-getA())*(s-getB())*(s-getC()));//
	return 0;
}
double Triangle::perimeter(){//returns the perimeter of the triangle
	return getA() + getB() + getC();
}
