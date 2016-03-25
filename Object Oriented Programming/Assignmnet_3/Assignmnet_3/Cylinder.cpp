#include "Cylinder.h"



Cylinder::Cylinder(){//consturctor
	setRadius(1);
	setHeight(1);
}
Cylinder::Cylinder(double radius, double height) {//sets the height and radius
	setRadius(radius);
	setHeight(height);
}
double Cylinder::area(){//returns the area of the cylinder
	return 3.14 * (getRadius()*getRadius()) + 2*3.14*getRadius()*getHeight();

}
double Cylinder::volume(){//returns the volume of the cylinder
	return 3.14 * (getRadius()*getRadius()) * getHeight();
}
