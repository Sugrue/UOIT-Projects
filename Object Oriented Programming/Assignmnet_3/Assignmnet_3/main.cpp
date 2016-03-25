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
	vector <Shape *> shapeList;

	char charResponse = ' ';
	double dblInput[3];
	double dblPerimeter = 0;
	double dblArea = 0;
	double dblVolume = 0;
	Triangle* ptrTempTriangle;

	const char CIRCLE = 'C';
	const char SQUARE = 'S';
	const char TRIANGLE = 'T';
	const char SPHERE = 'P';
	const char CYLINDER = 'Y';
	const char DISPLAY = 'D';
	const char QUIT = 'Q';

	//checks the input to see whether or not to close the program
	while (charResponse != 'Q')
		
	{
		//Outputs options for user to input
		cout<<CIRCLE<<" \t\tCreate a Circle"<<endl
			<<SQUARE<<" \t\tCreate a Square"<<endl
			<<TRIANGLE<<" \t\tCreate a Triangle"<<endl				
			<<SPHERE<<" \t\tCreate a Sphere"<<endl
			<<CYLINDER<<" \t\tCreate a Cylinder"<<endl<<endl
			<<DISPLAY<<" \t\tDisplay all shapes"<<endl<<endl
			<<QUIT<<" \t\tTo Quit the program"<<endl<<endl<<endl;
		cout <<"What would you like to do: ";
		//takes in input
		cin>>charResponse;	
		//makes upercase
		charResponse = toupper(charResponse);						

		//use to check the input to see what to do next
		switch (charResponse)										
		{
		case CIRCLE:
			//ask for the radius to be specified
			cout<<"What is the radius of the Circle: ";				
			cin>>dblInput[0];

			//if circle creates a new object in the shapeList for the new circle
			shapeList.insert(shapeList.end(), new Circle(dblInput[0])); 
			break;
		case SQUARE:
			cout<<"What is the length of one of the square's sides: ";//ask for the side lenght to be specified
			cin>>dblInput[0];

			shapeList.insert(shapeList.end(), new Square(dblInput[0]));//if a square, creates a new object in the shapeList for the new square
			break;
		case TRIANGLE:
			do { //checks if triangle, if not loops
				cout<<"What is the length of:"<<endl
					<<"Side A:";
				cin>>dblInput[0];
				cout<<"Side B:";											//ask of the sides lengths of the triangle
				cin>>dblInput[1];
				cout<<"Side C:";
				cin>>dblInput[2];

				ptrTempTriangle =  new Triangle(dblInput[0],dblInput[1],dblInput[2]);

				if(!ptrTempTriangle->isTriangle()) {
					cout<<endl
						<<"Error. The length entered do not form a triangle. Please try again."<<endl<<endl;
					delete ptrTempTriangle;
				}
				
			} while (!ptrTempTriangle->isTriangle());

			
			shapeList.insert(shapeList.end(), ptrTempTriangle);// creates new object in the shapeList for the new triangle
			ptrTempTriangle = 0;

			break;
		case SPHERE:
			cout<<"What is the radius of the Sphere: ";					//ask for the radius of the sphere
			cin>>dblInput[0];

			shapeList.insert(shapeList.end(), new Sphere(dblInput[0]));//creates new object in shapeList for the new sphere
			break;
		case CYLINDER:
			cout<<"What is the radius of the Cylinder: ";	
			cin>>dblInput[0];											//ask of the height and radius of cylinder
			cout<<"What is the height of the Cylinder: ";
			cin>>dblInput[1];
			
			shapeList.insert(shapeList.end(), new Cylinder(dblInput[0],dblInput[1]));//creates new object in the shapeList for the new cylinder
			break;
		case DISPLAY:

			cout<<endl<<endl<<"\t\tShape\t\tPerimeter\tArea\tVolume"<<endl;			//prints out the headings for the display

			for (int i = 0; i < shapeList.size(); i++) {	//loop to check the shapeList for different types

				if (dynamic_cast<Circle*>(shapeList[i])) {//used to check to list to see where the CIRCLE shapes are
					cout<<"Shape: "<<i<<"\tCircle  \t"<<shapeList[i]->perimeter()<<"\t\t"<<shapeList[i]->area()<<"\t"<<"N/A"<<endl;
					dblPerimeter += shapeList[i]->perimeter();//adds the shapes perimeter to the total perimeter
					dblArea += shapeList[i]->area();//adds the shapes area to the total area
				}
				else if (dynamic_cast<Square*>(shapeList[i])) {//checks the list to see the SQUARE shapes are
					cout<<"Shape: "<<i<<"\tSquare  \t"<<shapeList[i]->perimeter()<<"\t\t"<<shapeList[i]->area()<<"\t"<<"N/A"<<endl;
					dblPerimeter += shapeList[i]->perimeter();
					dblArea += shapeList[i]->area();//adds the shapes area to the total area
				}
				else if (dynamic_cast<Triangle*>(shapeList[i])) {//checks the list to see where the TRIANGLE shapes are
					cout<<"Shape: "<<i<<"\tTriangle\t"<<shapeList[i]->perimeter()<<"\t\t"<<shapeList[i]->area()<<"\t"<<"N/A"<<endl;
					dblPerimeter += shapeList[i]->perimeter();//adds the shapes perimeter to the total perimeter
					dblArea += shapeList[i]->area();//adds the shapes area to the total area
				}
				else if (dynamic_cast<Sphere*>(shapeList[i])) {//checks the list to see where the SPHERE shapes are
					cout<<"Shape: "<<i<<"\tSphere  \t"<<"N/A\t\t"<<shapeList[i]->area()<<"\t"<<shapeList[i]->volume()<<endl;
					dblVolume += shapeList[i]->volume();//adds the shapes volume to the total volume
					dblArea += shapeList[i]->area();//adds the shapes area to the total area
				}
				else if (dynamic_cast<Cylinder*>(shapeList[i])) {//checks the list to see where the CYLINDER shapes are
					cout<<"Shape: "<<i<<"\tCylinder  \t"<<"N/A\t\t"<<shapeList[i]->area()<<"\t"<<shapeList[i]->volume()<<endl;
					dblVolume += shapeList[i]->volume();//adds the shapes volume to the total volume
					dblArea += shapeList[i]->area();//adds the shapes area to the total area
				}
			}

			cout<<"Total:\t\t\t\t"<<dblPerimeter<<"\t\t"<<dblArea<<"\t"<<dblVolume<<endl<<endl;//outputs the totals of everything
			system("pause");
			break;
		case QUIT:
			return 0;//ends program
			break;
		default:
			cout<<charResponse<<" is invaild. Please enter a vaild reponse."<<endl;//Error Responce
			break;
		}
	}	
}


