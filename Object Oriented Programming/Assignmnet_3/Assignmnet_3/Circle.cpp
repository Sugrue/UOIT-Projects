#include "Circle.h"



Circle::Circle(){//consturctor
	setA(1);
}
Circle::Circle(double radius){//sets the radius
	setA(radius);
}
double Circle::area(){//returns the area
	return getA() * getA();

}
double Circle::perimeter(){//returns the perimeter
	return 2*3.14*getA() ;
}
