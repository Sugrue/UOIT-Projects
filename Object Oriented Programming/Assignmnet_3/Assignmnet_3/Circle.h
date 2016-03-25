#include "TwoDShape.h"
#ifndef CIRCLE_H
#define CIRCLE_H


class Circle:public TwoDShape{
public:
	Circle();//constructor
	
	Circle(double radius);//sets the new radius
	virtual double area();	//calculates area, virutal so compiler uses the lowest one in the inheritance
	virtual double perimeter();	//calculates perimeter, virutal so compiler uses the lowest one in the inheritance
};
#endif
