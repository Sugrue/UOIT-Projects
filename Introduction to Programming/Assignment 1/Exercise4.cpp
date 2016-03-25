#include <iostream>;
using namespace std;

int RandomNum(int intBaseValue, int intMaxValue) {
	//Function to calculate any random number within a supplied range
	return rand() % (intMaxValue - intBaseValue + 1) + intBaseValue;
}

int main () {
	//Variable and constant declaration
	int intNumber = 0, intGuess = 0; //random number and the users guess
	char charLoop = 'y', charResponse = 'z'; //loop control values

	//Max and min values to be used in the random number calculation
	const int MAXNUM = 1000;
	const int MINNUM = 1;

	//Initiation of the loop to keep repeating the game
	while (charLoop == 'y')
	{
		//Requesting the users guess
		cout<<"I have a number between "<<MINNUM<<" and "<<MAXNUM<<endl
			<<"Can you guess my number?"<<endl;

		//Calculating the random number
		intNumber = RandomNum(MINNUM, MAXNUM);

		//Initiation of the loop to keep requesting guesses from the user until the correct number if guessed
		while (intGuess != intNumber)
		{
			//Requesting the users next guesses
			cout<<"Please type your guess."<<endl;
			cin>>intGuess;

			//comparing the users guessed number to the computer generated value, outputs the appropriate response
			if (intGuess > intNumber)
				cout<<endl<<"Too high. Try again."<<endl;
			else if (intGuess < intNumber)
				cout<<endl<<"Too low. Try again."<<endl;
		}

		//Confirms the correct guess
		cout<<"Excellent! You guessed the number!"<<endl;

		//Loop to obtain the users response, (play again)
		do
		{
			cout<<"Would you like to play again (y or n)"<<endl;
			cin>>charResponse;
			//if the characters aren’t valid, the user is prompt again for a valid character
		} while (charResponse != 'y' && charResponse != 'n');

		//Sets the user’s valid character as the response, thus either relooking the program or exiting it
		charLoop = charResponse;
	}


	system("Pause");
	return 0;
}
