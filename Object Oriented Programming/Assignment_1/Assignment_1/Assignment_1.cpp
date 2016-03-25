#include <iostream>
using namespace std;

int main()           
{
	const int HEADERLENGTH = 54;	
	//contains the header length, thus the program may be adapted if the standard were to change
	
	char header[HEADERLENGTH+1];	
	//Char array to access header, the + 1 accounts for the cin function adding the null charater at the end of the cstring
	char byte;						
	//stores byte of information from the image
	int i;							
	//used as a counter

	//populates the header cstring & since no modifications need to be done to it, the program passes it straight to the output file
	for (i = 0; i<=54; i++) {	
		cin.get(header[i]);
		cout << header[i];
	}	

	//reset the counter for the while loop
	i = 0;

	//applies the modifications to the bytes within the image file and passes them to the output file
	while(cin.get(byte)) {
		cout<<(char) (255-byte); //credit to Slawomir Kmiec for inversion of bytes (graphical reversion)
		i++;
	}

	return 0;
}