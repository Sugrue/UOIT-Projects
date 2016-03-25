#include <iostream>
#include "SLList.h"

using namespace std;

/*
Create a Link List object
2. Add at least 3 strings to the list
3. Search for one of the strings by name
4. Search for one of the strings by ID
5. Display changes as nessary

*/
void cls(){
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl 
		 << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
}

int main(){

	SLList list;

	cout << "1: Add at least 3 strings to the list" << endl;
	list.insertLast("Kyle", 1);
	list.insertLast("Scott", 2);
	list.insertFirst("Dalton", 3);

	list.print();

	system("pause");
	cls();

	cout << endl << "2: Search for one of the strings by name" << endl;
	cout << "Searching for ""Kyle""" << endl;

	if (list.searchName("Kyle"))
		cout << "Name has been found" << endl;
	else
		cout << "Name was not found" << endl;


	system("pause");
	cls();


	cout << endl << "3: Search for one of the strings by ID" << endl;
	cout << "Searching for ""3""" << endl;

	if (list.searchID(3))
		cout << "ID was found" << endl;
	else
		cout << "ID wasa not found" << endl;


	system("pause");
	cls();

	list.print();

system("pause");
return 0;
}