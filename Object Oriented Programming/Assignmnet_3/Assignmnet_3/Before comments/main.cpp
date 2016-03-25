#include <iostream>;
#include <string>;
#include <vector>;



#include "Circle.h";
#include "Square.h";
#include "Triangle.h";
#include "Cylinder.h";
#include "Sphere.h";

using namespace std;

int main(){
	// Find my UML attached. Its mostly accurate. I did find a ton of errors in my uml and your UML.
	
	vector <Shape *> shapeList;

	char charResponse = ' ';
	double dblInput[3];
	double dblPerimeter = 0;
	double dblArea = 0;
	double dblVolume = 0;

	const char CIRCLE = 'C';
	const char SQUARE = 'S';
	const char TRIANGLE = 'T';
	const char SPHERE = 'P';
	const char CYLINDER = 'Y';
	const char DISPLAY = 'D';
	const char QUIT = 'Q';

	while (charResponse != 'Q')
	{
		cout<<CIRCLE<<" \t\tCreate a Circle"<<endl
			<<SQUARE<<" \t\tCreate a Square"<<endl
			<<TRIANGLE<<" \t\tCreate a Triangle"<<endl
			<<SPHERE<<" \t\tCreate a Sphere"<<endl
			<<CYLINDER<<" \t\tCreate a Cylinder"<<endl<<endl
			<<DISPLAY<<" \t\tDisplay all shapes"<<endl<<endl
			<<QUIT<<" \t\tTo Quit the program"<<endl<<endl<<endl;
		cout <<"What would you like to do: ";
		cin>>charResponse;
		charResponse = toupper(charResponse);

		switch (charResponse)
		{
		case CIRCLE:
			cout<<"What is the radius of the Circle: ";
			cin>>dblInput[0];

			shapeList.insert(shapeList.end(), new Circle(dblInput[0]));
			break;
		case SQUARE:
			cout<<"What is the length of one of the square's sides: ";
			cin>>dblInput[0];

			shapeList.insert(shapeList.end(), new Square(dblInput[0]));
			break;
		case TRIANGLE:
			cout<<"What is the length of:"<<endl
				<<"Side A:";
			cin>>dblInput[0];
			cout<<"Side B:";
			cin>>dblInput[1];
			cout<<"Side C:";
			cin>>dblInput[2];

			shapeList.insert(shapeList.end(), new Triangle(dblInput[0],dblInput[1],dblInput[2]));
			break;
		case SPHERE:
			cout<<"What is the radius of the Sphere: ";
			cin>>dblInput[0];

			shapeList.insert(shapeList.end(), new Sphere(dblInput[0]));
			break;
		case CYLINDER:
			cout<<"What is the radius of the Cylinder: ";
			cin>>dblInput[0];
			cout<<"What is the height of the Cylinder: ";
			cin>>dblInput[1];
			
			shapeList.insert(shapeList.end(), new Cylinder(dblInput[0],dblInput[1]));
			break;
		case DISPLAY:

			cout<<endl<<endl<<"\t\tShape\t\tPerimeter\tArea\tVolume"<<endl;

			for (int i = 0; i < shapeList.size(); i++) {

				if (dynamic_cast<Circle*>(shapeList[i])) {
					cout<<"Shape: "<<i<<"\tCircle  \t"<<shapeList[i]->perimeter()<<"\t\t"<<shapeList[i]->area()<<"\t"<<"N/A"<<endl;
					dblPerimeter += shapeList[i]->perimeter();
					dblArea += shapeList[i]->area();
				}
				else if (dynamic_cast<Square*>(shapeList[i])) {
					cout<<"Shape: "<<i<<"\tSquare  \t"<<shapeList[i]->perimeter()<<"\t\t"<<shapeList[i]->area()<<"\t"<<"N/A"<<endl;
					dblPerimeter += shapeList[i]->perimeter();
					dblArea += shapeList[i]->area();
				}
				else if (dynamic_cast<Triangle*>(shapeList[i])) {
					cout<<"Shape: "<<i<<"\tTriangle\t"<<shapeList[i]->perimeter()<<"\t\t"<<shapeList[i]->area()<<"\t"<<"N/A"<<endl;
					dblPerimeter += shapeList[i]->perimeter();
					dblArea += shapeList[i]->area();
				}
				else if (dynamic_cast<Sphere*>(shapeList[i])) {
					cout<<"Shape: "<<i<<"\tSphere  \t"<<"N/A\t\t"<<shapeList[i]->area()<<"\t"<<shapeList[i]->volume()<<endl;
					dblVolume += shapeList[i]->volume();
					dblArea += shapeList[i]->area();
				}
				else if (dynamic_cast<Cylinder*>(shapeList[i])) {
					cout<<"Shape: "<<i<<"\tCylinder  \t"<<"N/A\t\t"<<shapeList[i]->area()<<"\t"<<shapeList[i]->volume()<<endl;
					dblVolume += shapeList[i]->volume();
					dblArea += shapeList[i]->area();
				}
			}

			cout<<"Total:\t\t\t\t"<<dblPerimeter<<"\t\t"<<dblArea<<"\t"<<dblVolume<<endl<<endl;
			system("pause");
			break;
		case QUIT:
			return 0;
			break;
		default:
			cout<<charResponse<<" is invaild. Please enter a vaild reponse."<<endl;
			break;
		}
	}

	




	
}


