#include <iostream>;
using namespace std;

int main(){
	//Variable declaration
	double dblAmountOfNumbers = 0, dblAverage = 0, dblNumber = 0;
	int intNumOfPositiveNum = 0;

	//requests user input for the amount of number he/she wishes to enter
	cout<<"Please enter the amount of numbers you wish to enter : "<<endl;
	cin>>dblAmountOfNumbers;

	for (int i = 1; i <= dblAmountOfNumbers; i++) {
		//Requests the numbers
		cout<<endl
			<<"Please enter a positive value = ";
		cin>>dblNumber;

		/*
		checks if the numbers are positive, if so calculates the new average
		also increments the count wish keeps track of number of numbers entered
		*/
		if (dblNumber >= 0) {
		dblAverage = (dblAverage + dblNumber)/i;
		intNumOfPositiveNum += 1;
		}
	}

	/*
	Output, checks if more than one positive number was entered by the user.
	if so the average is displayed, if not an error message is displayed
	*/
	if (intNumOfPositiveNum > 1)
		cout<<endl
			<<"The Average of all positive numbers entered is "<<dblAverage<<endl;
	else
		cout<<"Too few numbers were entered."<<endl;



	system("Pause");
	return 0;
}
