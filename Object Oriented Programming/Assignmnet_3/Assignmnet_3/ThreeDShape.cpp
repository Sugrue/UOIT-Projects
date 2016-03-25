#include "ThreeDShape.h"

ThreeDShape::ThreeDShape(){//constructor
height = 1;
radius = 1;

}
	void ThreeDShape::setHeight(double a){//sets the new hight
		height = a;
	}
	double ThreeDShape::getHeight(){//returns the height back to the main
		return height;
	}
		void ThreeDShape::setRadius(double a){//sets the new radius
		radius = a;
	}
	double ThreeDShape::getRadius(){//returns the radius back to the main
		return radius;
	}
	double ThreeDShape::area(){// passdown from the base
		return 0;
	}
	double ThreeDShape::volume(){//passed down from the base
		return 0;
	}