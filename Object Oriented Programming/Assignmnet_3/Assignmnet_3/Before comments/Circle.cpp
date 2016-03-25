#include "Circle.h"



Circle::Circle(){
	setA(1);
}
Circle::Circle(double radius){
	setA(radius);
}
double Circle::area(){
	return getA() * getA();

}
double Circle::perimeter(){
	return 2*3.14*getA() ;
}
