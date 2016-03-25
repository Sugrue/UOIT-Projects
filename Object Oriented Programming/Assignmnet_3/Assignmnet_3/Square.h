#include "TwoDShape.h"
#ifndef SQUARE_H
#define SQURE_H
class Square:public TwoDShape{
public:
	Square();//constructor
	Square(double side);//sets side
	virtual double area();	//calculates area, virutal so compiler uses the lowest one in the inheritance
	virtual double perimeter();	//calculates perimeter, virutal so compiler uses the lowest one in the inheritance
};
#endif