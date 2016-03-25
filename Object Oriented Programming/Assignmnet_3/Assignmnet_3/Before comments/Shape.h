
#include <string>
#include <iostream>
#ifndef SHAPE_H
#define SHAPE_H

class Shape{
public:
	//constructor
	Shape();


	virtual double area();
	virtual double perimeter();
	virtual double volume();
};
#endif