#include <iostream>;
#include <string>;

using namespace std;


int main () {
	const int NUMBERLENGTH = 8;

	char cardInput[NUMBERLENGTH+1];
	int cardNum[NUMBERLENGTH];
	int sumCheck1 = 0;
	int sumCheck2 = 0;
	int finalCheck = 0;
	int temp;


	cout<<"What is the card number:"<<endl<<"Number:";
	cin>>cardInput;

	for (int i=0; i<NUMBERLENGTH; i++) {
		if (isdigit(cardInput[i])) {
			cout<<"%DEBUG: Char: "<<cardInput[i];
			cardNum[i] = cardInput[i] - '0';
			cout<<" Int: "<<cardNum[i]<<endl;
		}
		else {
			cout<<"ERROR NOT A DIGIT:"<<cardInput[i]<<endl;
			system("Pause");
			return 0;
		}

	}

	cout<<"%DEBUG: starting check 1"<<endl;

	for (int i=NUMBERLENGTH-1; i>=0; i-=2) {
		cout<<"%DEBUG: i = "<<cardNum[i]<<" While sumcheck 1 is: "<<sumCheck1<<endl;
		sumCheck1+= cardNum[i];
	}
	
	cout<<"%DEBUG: ending check 1: with sumCheck1:"<<sumCheck1<<endl;

	cout<<"%DEBUG: starting check 2"<<endl;
	

	for (int i=NUMBERLENGTH-2; i>=0; i-=2) {
		temp = cardNum[i]*2;
		cout<<"%DEBUG: temp = "<<temp<<endl;

		while (temp >0) {
			sumCheck2+= temp % 10;
			cout<<"%DEBUG: %10 of temp: "<<temp%10<<" sumcheck = "<<sumCheck2<<endl;
			temp /= 10;
			cout<<"%DEBUG: Temp is now: "<<temp<<endl;
		}
	}

	cout<<"%DEBUG: ending check 2: with sumCheck2:"<<sumCheck2<<endl;

	cout<<"%DEBUG: starting final check"<<endl;

	finalCheck = sumCheck1 + sumCheck2;
	cout<<"%DEBUG: sumCheck1: "<<sumCheck1<<"sumCheck2: "<<sumCheck2<<" finalCheck: "<<finalCheck<<endl;


	if (finalCheck % 10 == 0)
		cout<<"The Card Number is Vaild"<<endl;
	else
		cout<<"The Card Number is invaild"<<endl;

	system("Pause");
	return 0;
}