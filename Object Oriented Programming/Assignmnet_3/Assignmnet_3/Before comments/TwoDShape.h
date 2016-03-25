#include "Shape.h"
#ifndef TWODSHAPE_H
#define TWODSHAPE_H
class TwoDShape:public Shape{
public:
	//Constructor
	TwoDShape();

	void setA(double a);
	void setB(double b);
	void setC(double c);
	double getA();
	double getB();
	double getC();

	virtual double area();
	virtual double perimeter();
	
private:
	double sideA;
	double sideB;
	double sideC;


};
#endif