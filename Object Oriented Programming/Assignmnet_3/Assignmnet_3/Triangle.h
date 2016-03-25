#include "TwoDShape.h"
#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle:public TwoDShape{
public:
	Triangle();//constuctor
	Triangle(double sideA, double sideB, double sideC);//sets sides to new values
	bool isTriangle();//checks to see if dementions make triangle
	virtual double area();	//calculates area, virutal so compiler uses the lowest one in the inheritance
	virtual double perimeter();//calculates perimeter, virutal so compiler uses the lowest one in the inheritance
};
#endif