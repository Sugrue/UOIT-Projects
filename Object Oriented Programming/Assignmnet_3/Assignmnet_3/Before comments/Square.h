#include "TwoDShape.h"
#ifndef SQUARE_H
#define SQURE_H
class Square:public TwoDShape{
public:
	Square();
	Square(double side);
	virtual double area();
	virtual double perimeter();




};
#endif