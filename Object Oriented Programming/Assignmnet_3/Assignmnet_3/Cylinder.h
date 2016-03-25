#include "ThreeDShape.h"
#ifndef CYLINDER_H
#define CYLINDER_H


class Cylinder:public ThreeDShape{
public:
	Cylinder();//constructor
	Cylinder(double radius, double height);//sets radius and height with new values
	virtual double area();//calculates area, virutal so compiler uses the lowest one in the inheritance
	virtual double volume();//calculates volume, virutal so compiler uses the lowest one in the inheritance
};
#endif