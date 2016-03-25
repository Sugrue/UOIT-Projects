#include "TwoDShape.h"
#ifndef CIRCLE_H
#define CIRCLE_H


class Circle:public TwoDShape{
public:
	Circle();
	Circle(double radius);
	virtual double area();
	virtual double perimeter();
};
#endif
