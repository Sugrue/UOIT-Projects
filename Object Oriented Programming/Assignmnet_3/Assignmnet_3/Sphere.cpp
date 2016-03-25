#include "Sphere.h"



Sphere::Sphere(){//constuctor 
	setRadius(1);
}
Sphere::Sphere(double radius) {//sets the radius
	setRadius(radius);
}
double Sphere::area(){//returns the area of the sphere
	return 4*3.14 * (getRadius()*getRadius());

}
double Sphere::volume(){//returns the volunme of the sphere
	return (4/3)*(3.14*((getRadius()*getRadius()*getRadius())));
}
