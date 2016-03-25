#include <iostream>;
using namespace std;

int main() {
	//Variable and Constant declaration
	const double MONFRI8TO6 = 0.4; //Call rate Monday to Friday: 8am to 6pm
	const double MONFRI6TO8 = 0.25; //Call rate Monday to Friday: 6pm to 8 am
	const double SATSUN = 0.15; //Call rate Saturday and Sunday

	int intLength, intTimeStarted; //the length of the call and the time started
	char charDay, charLoop = 'N', charResponse; //the character representing the day, the character used to satisfy the condition of the loop and the input of the user during the loop
	double dblCharge; //the charge of the call

	//initiation of the loop, keeps asking for new input from the user until they wish to end the program
	while ( charLoop == 'N') {

		//Requesting input from the user, the day in question
		cout<<"Please enter the day of the week"<<endl
			<<"M = Monday"<<endl
			<<"T = Tuesday"<<endl
			<<"W = Wednesday"<<endl
			<<"R = Thursday"<<endl
			<<"F = Friday"<<endl
			<<"S = Saturday"<<endl
			<<"U = Sunday"<<endl
			<<"Please enter the day of the week: ";
		cin>>charDay;

		//Requesting the time the call was initiated
		cout<<endl
			<<"Please enter the time the call was intitiated in 24hour time. IE 1:30PM = 1330"<<endl
			<<"Inititiation of call:";
		cin>>intTimeStarted;

		//Requesting the duration of the call
		cout<<endl
			<<"Please enter the duration of the call"<<endl
			<<"Duration: ";
		cin>>intLength;

		//A switch case selecting the day
		switch(charDay) {
			case 'M':
			case 'm':
			case 'T':
			case 't':
			case 'W':
			case 'w':
			case 'R':
			case 'r':
			case 'F':
			case 'f':
				//Selecting the right charge to apply depending on the time of day, then calculating it
				if (intTimeStarted >= 800 && intTimeStarted <= 1800)
					dblCharge = MONFRI8TO6*intLength;
				else
					dblCharge = MONFRI6TO8*intLength;
				break;

			case 'S':
			case 's':
			case 'U':
			case 'u':
				//Calculating the charge for the day
				dblCharge = intLength * SATSUN;
				break;
		}

		//Outputting all the details of the call and checking if the user wishes to terminate the program
		cout<<endl
			<<"The total for your "<<intLength<<" minute call issued on "<<charDay<<" at "<<intTimeStarted<<" is "<<dblCharge<<endl

			<<"Would you like to Terminate the Program? (Y (Yes) or anykey (No)";
		cin>>charResponse;

		//setting the users response, if Y for yes then change the value, if another value is entered loop the program
		switch (charResponse) {
			case 'Y':
			case 'y':
				charLoop = 'Y';
				break;
		}
	}

	system("pause");
	return 0;
}
