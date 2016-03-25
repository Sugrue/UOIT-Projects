#include "Cylinder.h"



Cylinder::Cylinder(){
	setRadius(1);
	setHeight(1);
}
Cylinder::Cylinder(double radius, double height) {
	setRadius(radius);
	setHeight(height);
}
double Cylinder::area(){
	return 3.14 * (getRadius()*getRadius()) + 2*3.14*getRadius()*getHeight();

}
double Cylinder::volume(){
	return 3.14 * (getRadius()*getRadius()) * getHeight();
}
