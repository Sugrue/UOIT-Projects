#include "DoubleLinkedList.h"

bool Debug = false; //Set to true for Debug msgs


	DoubleLinkedList::DoubleLinkedList() {
		root = NULL;
		current = root;

		EOL = new Node;
		EOL ->next = 0;
		EOL->data = 987654321;

		if (Debug == true) {
			cout<<"The address of ROOT is:"<<root<<endl;
			cout<<"The address of Current is:"<<current<<endl<<endl;
		}
	

	} //constructor
	DoubleLinkedList::~DoubleLinkedList() {
		current = root;
		int i = 0;
		Node *temp;

		while (current ->next != 0) {
			temp = current;
			current = current->next;

			delete temp;
			i++;

			//deletes nodes, by setting temp to the current, moving current and deleting temp
		}
		

		delete current;
		cout<<i+1<<" Nodes where deleted."<<endl;
	}//Destructor
		
	int DoubleLinkedList::Size() {
		int i = -1; //makes the sizing initial number 0 IE root = 0 instead of 1

		Node *temp = new Node;

		if (Debug == true) {
			cout<<"%DEBUG: Size funciton called/started"<<endl;
			cout<<"%DEBUG: Temp Node/i created"<<endl;
		}

		temp = root;

		while (temp->next != 0) {
			if (Debug == true) {
				cout<<"%DEBUG: loop started"<<endl;
				cout<<"%DEBUG: Node:"<<i<<" Data: "<<temp->data<<endl;
			}

			temp = temp->next;
			
			if (Debug == true) {
				cout<<"%DEBUG: temp node set to next"<<endl;
			}

			i++;
		}

		return i;
		
		if (Debug == true) {
			cout<<"%DEBUG: loop completed, Size function completed"<<endl<<endl;
		}
		//It should support operation Size() to return the number of elements in the list
	}
	Node &DoubleLinkedList::Head() {
		return *root;

		if (Debug == true) {
			cout<<"%DEBUG: Reference to root returned: Root="<<root<<endl;
		}
		//It should support operation Head() to get the reference to first element of a list
	}
	Node &DoubleLinkedList::Tail() {
		Node *temp = new Node;
		temp = root;

		if (Debug == true) 
			cout<<"%DEBUG: Loop started."<<endl;

		while (temp->next != 0)
			temp = temp->next;

		temp = temp->previous;

		if (Debug == true) 
			cout<<"%DEBUG: Loop finished, last element: "<<temp<<endl;

		return *temp;
		//cycles through the list to find the tail

		//It should support operation Tail() to get the reference to the last element of a list
	}
	Node &DoubleLinkedList::Peek() {
		if (Debug == true) 
			cout<<"Current is :"<<current<<" DATA:"<<current->data<<endl;

		return *current;
		//It should support operation Peek() to get the reference to the currently pointed element of the list
	}
	Node &DoubleLinkedList::Top() {
		current = root;
		return *current;

		if (Debug == true) 
			cout<<"%DEBUG: root/current: "<<current<<endl; 

		//It should support operation Top() to set the current position in the list to the first element and return reference to it
	}
	Node &DoubleLinkedList::End() {
		if (Debug == true) 
			cout<<"%DEBUG: Loop started (END Fct)"<<endl;

		while (current->next != 0)
			current = current ->next;

		current = current ->previous;

		if (Debug == true) 
			cout<<"%DEBUG: End is: "<<current<<" DATA: "<<current->data<<endl;

		return *current;


		//It should support operation End() to set the current position in the list to the last element and return reference to it
	}
	Node &DoubleLinkedList::Add(int newData) {
		if (Debug == true) 
			cout<<"%DEBUG: Add function called"<<endl;
		
		Node *newNode = new Node;
		
		if (Debug == true) 
			cout<<"%DEBUG: New Node Created."<<endl;

		newNode ->data = newData;
		if (Debug == true) 
			cout<<"%DEBUG: Data Assigned to the new node."<<endl;
		

		newNode ->previous = current;
		if (Debug == true) 
			cout<<"%DEBUG: new nodes previous pointed set to current"<<endl;


		if (root == NULL)
		{
			root = newNode;
			current = newNode;
		}
		else
		{
			if (current ->next != EOL) {
				while (current->next != 0)
					current = current->next;
				current = current->previous;
			}

			current->next = newNode;
			if (Debug == true) 
				cout<<"%DEBUG: current's next pointer set to the new node"<<endl;
			current = current->next;
			if (Debug == true) 
				cout<<"%DEBUG: current node set to the new node"<<endl;
		}

		current ->next = EOL;
		EOL ->previous = newNode;
		if (Debug == true) {
			cout<<"%DEBUG: new nodes next pointed set to EOL"<<endl;
			cout<<"%DEBUG: Add function completed."<<endl<<endl;
		}

		return *newNode;
		//It should support operation add(e) to insert a new element on the list the current location and return reference to it
	}
	Node &DoubleLinkedList::Delete() {
	
		Node *temp = current;

		if (temp == EOL) {
			if (Debug == true) 
				cout<<"DEBUG: current is set to EOL, Cannot e deleted"<<endl;

			return *EOL;
		}
		else if (temp == root) {
			if (Debug == true) 
				cout<<"DEBUG: current is set to Root, next node is now being set as root."<<endl;

			temp->next->previous = 0;
			root = temp->next;
			current = root;

			delete temp;
			if (Debug == true) 
				cout<<"DEBUG: only root deleted"<<endl;

			return *current;
			
		} else if (temp->next == EOL) {
			temp->next->previous = temp->previous;
			cout<<"%DEBUG: previous of current/temp's is being set as previous of current/temp's next"<<endl;

			temp->previous->next = temp->next;
			cout<<"%DEBUG: next of current/temp is being set as next of current/temp's previous"<<endl;

			current = temp->previous;

			delete temp;
			return *current;
		} else {
			temp->next->previous = temp->previous;
			if (Debug == true) 
				cout<<"%DEBUG: previous of current/temp's is being set as previous of current/temp's next"<<endl;
			temp->previous->next = temp->next;
			if (Debug == true) 
				cout<<"%DEBUG: next of current/temp is being set as next of current/temp's previous"<<endl;
			
			current = temp->next;
		

			if (Debug == true) {
				cout<<"%DEBUG:temp/old current is deleted"<<endl;
				cout<<"%DEBUG: new current is: "<<current<<" DATA: "<<current->data<<endl;
			}

			return *current;
		}


		
		//It should support operation delete() to delete the current element of the list and return reference to the next element on the list
	}

	Node &DoubleLinkedList::operator ++()
	{	
		if (current->next != EOL) {
			current = current->next;
			if (Debug == true) {
				cout<<"%DEBUG: old current: "<<current->previous<<" DATA:"<<current->previous->data<<endl;
				cout<<"%DEBUG: new current: "<<current<<" DATA:"<<current->data<<endl;
			}
			return *current;
		} else {
			if (Debug == true) 
				cout<<"%DEBUG: current is EOL, return EOL"<<endl;
			return *EOL;
		}
		//It should support prefix operator ++ to advance to the next element on the list and return reference to it
	}	
	Node &DoubleLinkedList::operator ++(int)
	{
		if (current->next != EOL) {
			current = current->next;
			if (Debug == true) {
				cout<<"%DEBUG: old current: "<<current->previous<<" DATA:"<<current->previous->data<<endl;
				cout<<"%DEBUG: new current: "<<current<<" DATA:"<<current->data<<endl;
			}
			return *current;
		} else {
			if (Debug == true) 
				cout<<"%DEBUG: current is EOL, return EOL"<<endl;
			return *EOL;
		}
		//It should support prefix operator ++ to advance to the next element on the list and return reference to it
	}
	Node &DoubleLinkedList::operator --()
	{
		if (current->previous != 0) {
			current = current->previous;
			if (Debug == true) {
				cout<<"%DEBUG: old current: "<<current->previous<<" DATA:"<<current->previous->data<<endl;
				cout<<"%DEBUG: new current: "<<current<<" DATA:"<<current->data<<endl;
			}
			return *current;
		} else {
			if (Debug == true)
				cout<<"%DEBUG: current is root, returned EOL"<<endl;
			return *EOL;
		}
		//It should support prefix operator -- to advance to the previous element on the list and return reference to it
	}
	Node &DoubleLinkedList::operator --(int)
	{
		if (current->previous != 0) {
			current = current->previous;
			if (Debug == true) {
				cout<<"%DEBUG: old current: "<<current->previous<<" DATA:"<<current->previous->data<<endl;
				cout<<"%DEBUG: new current: "<<current<<" DATA:"<<current->data<<endl;
			}
			return *current;
		} else {
			if (Debug == true)
				cout<<"%DEBUG: current is root, returned EOL"<<endl;
			return *EOL;
		}
		//It should support prefix operator -- to advance to the previous element on the list and return reference to it
	}
	Node &DoubleLinkedList::operator +(DoubleLinkedList& a)
	{
		DoubleLinkedList *newList = new DoubleLinkedList;
		Node *temp;
		

		if (Debug == true)
			cout<<"%DEBUG: temp set to root of first linked list"<<endl;

		temp = root;

		if (Debug == true)
			cout<<"%DEBUG: Loop started, adding first LinkedList to combined list"<<endl;

		while (temp->next != 0) {
			newList->Add(temp->data);

			if (Debug == true)
				cout<<"%DEBUG: adding node: "<<temp<<" DATA: "<<temp->data<<endl;

			temp = temp->next;
		}

		if (Debug == true)
			cout<<"%DEBUG: setting temp to head of second list"<<endl;

		temp = &a.Head(); 

		while (temp->next != 0) {
			if (Debug == true)
				cout<<"%DEBUG: adding node: "<<temp<<" DATA: "<<temp->data<<endl;
			newList->Add(temp->data);
			temp = temp->next;
		}
		
		
		temp = &newList->Head();

		if (Debug == true)
			cout<<"%DEBUG: returning root node of new list: "<<temp<<" DATA: "<<temp->data<<endl;

		return *temp;
		//It should support operator + to concatenate 2 double linked lists return reference to the head of the concatenated list
	}
	Node &DoubleLinkedList::operator [] (const int nIndex) {
	
		Node *temp = root;

		if (Debug == true)
			cout<<"%DEBUG: starting loop, walking through node till desired node of: "<<nIndex<<" is reached."<<endl;

		for (int i = 0; i < nIndex; i++) {
			if (temp->next != 0) {
				if (Debug == true)
					cout<<"%DEBUG: Next Node is vaild. Moving to next. Current: "<<temp<<" DATA: "<<temp->data<<" NEXT: "<<temp->next<<endl;
				temp = temp->next;

			} 
			else {
				if (Debug == true)
					cout<<"%DEBUG: EOL reached. Returning EOL"<<endl;
					return *EOL;
			}

		}

		return *temp;
	
	}






