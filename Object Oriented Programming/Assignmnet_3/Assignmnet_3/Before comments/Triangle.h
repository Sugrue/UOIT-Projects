#include "TwoDShape.h"
#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle:public TwoDShape{
public:
	Triangle();
	Triangle(double sideA, double sideB, double sideC);
	double isTriangle();
	virtual double area();
	virtual double perimeter();
};
#endif