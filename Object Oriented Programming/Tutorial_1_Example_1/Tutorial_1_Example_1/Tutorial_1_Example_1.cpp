#include <iostream>;

using namespace std;

void indexOfVal(int theArray[], int size)
{
	bool found = false;
	int index;
	int number;

	cout<<"Hey, you need a number? what number...?"<<endl;

	while (!found)
	{
		cout<<"Please enter a number?"<<endl;
		cin>>number;

		for (int i = 0; i<size; i++)
			if (theArray[i] == number)
			{
				cout<<"Found it! The number "<<number<<"is at index"<<i<<"i"<<endl;
				return;
			}
		cout<<"Couldnt find it"<<endl;

	}

}

int main() {
	const int maxSize = 5;
	int myArray[maxSize];

	int max;
	int min;
	int sum = 0;
	double average;

	cout<<"Hello!"<<endl;

	for (int i = 0; i<maxSize; i++) {
		cout<<"Please enter number "<<i+1<<endl;
		cin>>myArray[i];

		sum += myArray[i];

		if (i==0) 
			max=min=myArray[i];

		if (myArray[i] > max)
			max = myArray[i];

		if (myArray[i] < min)
			min = myArray[i];

	}
		average = sum/maxSize;
		cout<<endl<<endl<<"The max was: "<<max<<endl
			<<"The min was: "<<min<<endl
			<<"The average was: "<<average<<endl;

		indexOfVal(myArray, maxSize);

		system("Pause");
		return 0;
	}