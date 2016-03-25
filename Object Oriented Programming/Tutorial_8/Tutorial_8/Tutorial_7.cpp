#include<iostream>;
#include<vector>;

#include"Calc.h";
#include "betterCalc.h";

using namespace std;

int main () {

	vector <int> myVect;
	int temp;


	for (int i = 0; i < 4; i++) 
	{
		cout<<endl<<i<<" value: ";
		cin>> temp;
		myVect.insert(myVect.end(),temp);

		//myVect.push_back(temp);
	}

		for (int i = 0; i < 4; i++) 
	{
		cout<<endl<<"Vector item "<<i<<" = "<<myVect[i];
	}


		int index;
		
		cout<<endl<<endl<<"Relace at (0-4): ";
		cin>>index;
		cout<<endl<<"with what: ";
		cin>>temp;

		myVect[index]=temp;
		
			for (int i = 0; i < 4; i++) 
	{
		cout<<endl<<"Vector item "<<i<<" = "<<myVect[i];
	}
		for (int i = 0; i < 4; i++) 
	{
		myVect.pop_back();
	}

		cout<<endl<<"Size of vector: "<<myVect.size()<<endl<<endl;

		system("pause");
		return 0;



	int a,b;
	Calc myCalc;
	cout<<"Please enter the first integer"<<endl;
	cin>>a;
	cout<<"Please enter the second integer"<<endl;
	cin>>b;

	int sum = myCalc.add(a,b);
	int product = myCalc.multiply(a,b);
	int result = myCalc.divide(a,b);

	cout<<"The sum is: "<<sum<<endl<<"The product is: "<<product<<endl<<"The result is: "<<endl<<endl;


	//start of better calc
	cout<<"Start of the Bcalc"<<endl<<endl;

	double c,d;
	BetterCalc <double> myBCalc;

	cout<<"Please enter the first integer"<<endl;
	cin>>c;
	cout<<"Please enter the second integer"<<endl;
	cin>>d;

	double sum2 = myBCalc.add(c,d);
	double product2 = myBCalc.multiply(c,d);
	double result2 = myBCalc.divide(c,d);

	cout<<"The sum is: "<<sum2<<endl<<"The product is: "<<product2<<endl<<"The result is: "<<result2<<endl;

	system("Pause");
	return 0;

}