int myStrlen(char a[]) {

	//Variable declaration
	int intLength=0, i = 0;

	//Lopp that checks for the null character, increments counters to find length
	while(true){
		if (a[i] == '\0')
			break;
		i++;
		intLength++;
	}

	//Returns the length of the string. The -1 is to set the starting value of the string to 0 as opposed to 1
	return (intLength-1);
}
