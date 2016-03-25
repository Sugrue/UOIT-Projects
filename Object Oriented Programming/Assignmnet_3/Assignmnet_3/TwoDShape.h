#include "Shape.h"
#ifndef TWODSHAPE_H
#define TWODSHAPE_H
class TwoDShape:public Shape{
public:
	TwoDShape();//Constructor

	void setA(double a);//sets a new value to sideA
	void setB(double b);//sets a new value to sideB
	void setC(double c);//sets a new value to sideC
	double getA();//returns value of sideA
	double getB();//returns value of sideB
	double getC();//returns value of sideC

	
	virtual double area();//calculates area, virutal so compiler uses the lowest one in the inheritance
	
	virtual double perimeter();//calculates perimeter, virutal so compiler uses the lowest one in the inheritance
	
private:
	double sideA;//variable for sideA
	double sideB;//variable for sideB
	double sideC;//variable for sideC


};
#endif