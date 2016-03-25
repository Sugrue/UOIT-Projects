int count(char a[], char c){

	//Variable declaration
	int intOccur = 0, intLength = strlen(a);

	//Loop checks for the number of repetition of the specified char
	for (int i =0; i<intLength;i++){
		if (c == a[i])
			intOccur++;
	}

	//Returns the results
	return intOccur;
}
