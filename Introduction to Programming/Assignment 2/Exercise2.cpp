#include <iostream>;
using namespace std;

int main() {
	char charInputStr[100];
	int intLength;
	bool boolPalindrom = true;

	//Request user input
	cout<<"Please enter a pallindrome to be checked:"<<endl;
	cin>>charInputStr;
	cout<<endl;

	//store length to be used later
	intLength = strlen(charInputStr);

	//Loop that compairs charaters to determine if a pallindrome
	for (int i =0; i < intLength; i++) {
		if (charInputStr[i] != charInputStr[intLength-i-1]){
			boolPalindrom = false;
			break;
		}
	}

	//Output, depends on the results of the loop/check
	if (boolPalindrom)
		cout<<charInputStr<<" is a palindrom";

	system("pause");
	return 0;
}
