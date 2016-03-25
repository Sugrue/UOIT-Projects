#include "ThreeDShape.h"
#ifndef SPHERE_H
#define SPHERE_H


class Sphere:public ThreeDShape{
public:
	Sphere();
	Sphere(double radius);
	virtual double area();
	virtual double volume();
};
#endif