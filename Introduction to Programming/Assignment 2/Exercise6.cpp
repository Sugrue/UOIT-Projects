void padRight(char a[], int n) {

	//Variable declaration
	int i, intLength;

	//Variable initiation
	i = intLength = strlen(a);

	//Checks if the requested string length is larger than the strings allocated memory
	if (n <= 80)

		//Adds padding if needed
		for (i ; i <= n; i++)
			a[i] = '1';

	//Resets the strings null character delimiter
	a[i] = '\0';
}
