void trimLeft(char a[]){
	//Variable delectation, and initialization
	int shift=0;

	//Searches from the left for the end of the leading blanks
	for(int k=0;k<strlen(a);k++){
		if(a[k]==' ')
			shift++;
		else
			break;
	}

	//Copies the start of the characters to the start of the string
	for(int k=0;k<strlen(a)-shift;k++){
		a[k]=a[k+shift];
	}

	//Sets the delimitation character
	a[strlen(a)-shift]='\0';
}
