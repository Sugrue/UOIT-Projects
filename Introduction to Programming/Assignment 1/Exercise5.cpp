#include <iostream>;
using namespace std;

int main() {
	//Variable declaration
	int intLines = 0, intSpaces = 0, intStars = 0; //stores the amount of lines; stores the amount of spaces IE. " " to be entered per line; stores the amount of * per line

	//prompts the user to enter the amount of lines the generated triangle should have
	cout<<"Please enter the amount of lines of the triangle to be generated"<<endl;
	cin>>intLines;

	//Loops through everyline of the triangle printing one line at a time
	for (int i = 1; i <= intLines; i++)
	{
		//Calculates the number of spaces to be added at the start of the line (formatting)
		intSpaces = intLines - i;

		//Calculates the number of stars to be added to build the triangle
		intStars = 2*i - 1;

		//Prints out the spaces to give the triangle the right shape
		for (int j = 1; j <= intSpaces; j++)
			cout<<" ";
		//Prints out the * for a given line
		for (int j = 1; j <= intStars; j++)
			cout<<"*";

		//resets the cursor for the next line of the triangle
		cout<<endl;
	}

	system("Pause");
	return 0;
}
