#include <iostream>;
using namespace std;

int main()
{
	//Variable declaration
	int intNum[9]; //Stores user input
	int intMax=0, intOccur=0; //Store the assumed max value, and its occurrence

	//Requests user input
	cout<<"Please enter 10 numbers"<<endl;

	for (int i=0; i<10; i++){
		cout<<"Please enter the "<<i+1<<" Number: \t";
		cin>>intNum[i];
		cout<<endl;
	}

	//Checks the first value entered against all others, increases the occurrence value
	//if an identical value is found. Also resets the occurrence timer if the largest
	//value changes.
	intMax = intNum[0];

	for (int i=0; i<10; i++){
		if (intMax < intNum[i]){
			intMax = intNum[i];
			intOccur = 0;
		}
		if (intMax == intNum[i])
			intOccur++;
	}

	//Outputs the results
	cout<<endl
		<<"Largest Number: \t\t"<<intMax<<endl
		<<"Number of Occurrences: \t\t"<<intOccur<<endl;

	system("pause");
	return 0;
}
