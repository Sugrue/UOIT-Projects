#include "ThreeDShape.h"
#ifndef CYLINDER_H
#define CYLINDER_H


class Cylinder:public ThreeDShape{
public:
	Cylinder();
	Cylinder(double radius, double height);
	virtual double area();
	virtual double volume();
};
#endif