#include <iostream>
#include <string>
#include "DoubleLinkedList.h"
using namespace std;

int main() {
	int intTemp;
	DoubleLinkedList LinkedList;
	Node *test;
	DoubleLinkedList SecondLinkedList;

	for(int i = 0; i <4; i++) {
		cout<<"Create Node: "<<i<<" Enter value:";
		cin>>intTemp;

		test = &LinkedList.Add(intTemp);

		cout<<"NODE = "<<test->data<<endl<<endl;


	}

	test = &LinkedList.Head();

	cout<<"%DEBUG: The head data value is: "<<test->data<<endl;


	test = &LinkedList.Delete();
	cout<<"%DEBUG: Deleted current, its next value is: "<<test->data<<endl;

	cout<<"%DEBUG: The total number of Nodes is: "<<LinkedList.Size()<<endl;

	test = &LinkedList.Tail();
	cout<<"%DEBUG: The Tail data value is: "<<test->data<<endl;

	
	test = &LinkedList[1];

	cout<<"%DEBUG: The Second Node is: "<<test->data<<endl;

	test = &LinkedList++;

	cout<<"%DEBUG: The Node after current is: "<<test->data<<endl;

	test = &LinkedList--;
	cout<<"%DEBUG: The Third Node is: "<<test->data<<endl;




	for(int i = 0; i <4; i++) {
		cout<<"Create Node: "<<i<<" Enter value:";
		cin>>intTemp;

		test = &SecondLinkedList.Add(intTemp);

		cout<<"NODE = "<<test->data<<endl<<endl;


	}


	*test = LinkedList + SecondLinkedList;


	int i = 0;

	do {
		cout<<"%DEBUG: linked list node: "<<i<<" DATA: "<<test->data<<endl;
		test = test->next;
		i++;
	} while (test->next != 0);



system("pause");
return(0);
}