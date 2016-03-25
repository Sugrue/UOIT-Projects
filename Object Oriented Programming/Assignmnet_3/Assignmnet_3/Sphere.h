#include "ThreeDShape.h"
#ifndef SPHERE_H
#define SPHERE_H


class Sphere:public ThreeDShape{
public:
	Sphere();//constructor
	Sphere(double radius);//sets radius with new value
	virtual double area();//calculates area, virutal so compiler uses the lowest one in the inheritance
	virtual double volume();//calculates volume, virutal so compiler uses the lowest one in the inheritance
};
#endif