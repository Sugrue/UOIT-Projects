
#include <string>
#include <iostream>
#ifndef SHAPE_H
#define SHAPE_H

class Shape{
public:
	Shape();//constructor
	virtual double area();//calculates area, virutal so compiler uses the lowest one in the inheritance
	virtual double perimeter();	//calculates perimeter, virutal so compiler uses the lowest one in the inheritance
	virtual double volume();	//calculates volume, virutal so compiler uses the lowest onein the inheritance
};
#endif