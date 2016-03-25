//main.cpp
#include <iostream>

using namespace std;

struct Node{
	//data section
	int x;

	//pointer to the next object in the list
	Node* next;

	//constructor
	Node(){
		next = 0;
	}
}*root;

void insertNode (int index, int value, Node *root) {
	Node *p;
	p = root;

	for (int i = 1; i<index; i++)
	{
		if (p->next)
		{
			p = p->next;
		}
		else
		{
			cout<<"Index was outside of bounds"<<endl;
			return;
		}
	}

	Node *newNode = new Node;
	newNode ->x = value;
	newNode ->next = p->next;
	p->next = newNode;


}

int main(){
	cout<<"Let's make some nodes!"<<endl<<endl;
	int p;
	for (int i = 0;i<5;i++)
	{
		cout<<"Please enter a number for the data section of node "<<i+1<<endl;
		cin>>p;

		//make a new node
Node *newNode = new Node;
		//set the x value of our node equal to the number from our cin
		newNode->x = p;
		//if it's our first node
		if (root == NULL)
		{
			//set root equal to this node
			root = newNode;
		}
		//if it's not the first one, loop until we're at the end
		else
		{
			//make a temporary node and set it to root
			Node *p;
			p = root;

//while this node's X value does not equal 0, make it equal to the next one in line
			while(p->next != 0)
			{
				//temp node equals the next node
				p = p->next;
			}
			//when this loop breaks, p->next will be 0 (the end of our list) so make this end node, the newNode
			p->next = newNode;
		}
	}


	//output them all
	Node *temp;
	temp = root;

	cout<<endl<<"Done! Let's see them all now"<<endl;

	//similar loop, only now we're outputting the X value too
	while(temp->next != 0)
	{
		cout<<temp->x<<endl;
		temp = temp->next;
	}
	//and the last one
	cout<<temp->x<<endl;

	system("Pause");
	return 0;
}

