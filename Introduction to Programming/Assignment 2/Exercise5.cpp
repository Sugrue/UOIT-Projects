void trimRight(char a[]){

	//Variable declaration
	int intLength, intLastBlank;

	//Variable initialization
	intLastBlank = intLength = strlen(a);

	//Loop that detects blanks and indicates the last blanks position starting from the right.
	//-1 is issued to the length variable to skip the null character delimiter that would occur in the "length" position
	for (int i=(intLength-1); i>=0; i--)
		if (a[i] == ' ')
			intLastBlank--;
		else
			break;

	//Resets the null character delimiter at the edge of the string characters
	a[intLastBlank]='\0';
}
