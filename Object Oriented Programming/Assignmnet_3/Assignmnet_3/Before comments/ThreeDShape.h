#include "Shape.h"
#ifndef THREEDSHAPE_H
#define THREEDSHAPE_H
class ThreeDShape:public Shape{
public:
	//Constructor
	ThreeDShape();

	void setHeight(double a);
	double getHeight();
	void setRadius(double a);
	double getRadius();

	virtual double area();
	virtual double volume();
	
private:
	double height;
	double radius;


};
#endif