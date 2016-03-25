#include "Shape.h"
#ifndef THREEDSHAPE_H
#define THREEDSHAPE_H
class ThreeDShape:public Shape{
public:
	ThreeDShape();//Constructor
	void setHeight(double a);//sets the new hight
	double getHeight();//returns the hight
	void setRadius(double a);//sets the new radius
	double getRadius();//returns the radius

	virtual double area();//calculates area, virutal so compiler uses the lowest one in the inheritance
	
	virtual double volume();//calculates volume, virutal so compiler uses the lowest one in the inheritance
	
private:
	double height;//height of the object
	double radius;//radius of the object
};
#endif