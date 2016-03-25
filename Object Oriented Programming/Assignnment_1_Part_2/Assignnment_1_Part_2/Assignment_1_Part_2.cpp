#include <iostream>
using namespace std;

int main()           
{
	const char BLACK = NULL;
	//The ASCII equivilant to the binary value of black in a 24-bit BMP file
	const int ISHEADERFEILD = 34;
	//contains the image size feild starting byte, thus the program may be adapted if the standard were to change
	const int HEADERLENGTH = 54;
	//contains the header length, thus the program may be adapted if the standard were to change
	char header[HEADERLENGTH+1];
	//Char array to access header, the + 1 accounts for the cin function adding the null charater at the end of the cstring
	
	char byte;
	//temporary stores bytes
	int i;
	//used as counter
	int size;
	//stores the size of the image data within the file



	//loads the header within a cstring
	for (i = 0; i<=HEADERLENGTH; i++) {
		cin.get(header[i]);
		cout << header[i];
	}	

	//copies over the image data size from its feild into an interger by use of pointers
	*((char*)&size + 0) = header[ISHEADERFEILD + 0];
	*((char*)&size + 1) = header[ISHEADERFEILD + 1];
	*((char*)&size + 2) = header[ISHEADERFEILD + 2];
	*((char*)&size + 3) = header[ISHEADERFEILD + 3];	

	//resets the counter value
	i = 0;

	//loops through all the image data
	while(cin.get(byte)) {
		
		if (i > (size/2))
			cout<<BLACK; //paints the top half of a 24bit BMP file black, the top half is the last half of the file 
		else
			cout<<(char) (255-byte); //credit to Slawomir Kmiec for inversion of bytes (graphical reversion)
		i++;
	}

	return 0;

}
