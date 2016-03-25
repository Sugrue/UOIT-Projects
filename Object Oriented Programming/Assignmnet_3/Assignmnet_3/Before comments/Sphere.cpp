#include "Sphere.h"



Sphere::Sphere(){
	setRadius(1);
}
Sphere::Sphere(double radius) {
	setRadius(radius);
}
double Sphere::area(){
	return 4*3.14 * (getRadius()*getRadius());

}
double Sphere::volume(){
	return (4/3)*(3.14*((getRadius()*getRadius()*getRadius())));
}
