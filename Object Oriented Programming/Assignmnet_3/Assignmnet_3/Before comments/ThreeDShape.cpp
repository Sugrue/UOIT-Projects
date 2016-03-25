#include "ThreeDShape.h"

ThreeDShape::ThreeDShape(){
height = 1;
radius = 1;

}
	void ThreeDShape::setHeight(double a){
		height = a;
	}
	double ThreeDShape::getHeight(){
		return height;
	}
		void ThreeDShape::setRadius(double a){
		radius = a;
	}
	double ThreeDShape::getRadius(){
		return radius;
	}
	double ThreeDShape::area(){
		return 0;
	}
	double ThreeDShape::volume(){
		return 0;
	}