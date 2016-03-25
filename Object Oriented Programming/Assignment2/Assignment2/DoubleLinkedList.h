#include <iostream>
#include <string>
using namespace std;

struct Node {
	int data;
	Node* next;
	Node* previous; 

	Node () {
		next = 0;
		previous = 0;
	}
};

class DoubleLinkedList{


private:
	Node *root;
	Node *current;
	Node *EOL;
	int a;

public:

	int Size();
	Node &Head();
	Node &Tail();
	Node &Peek();
    Node &Top();
	Node &End();
	Node &Add(int newData);
	
	Node &Delete();

	DoubleLinkedList(); //constructor
	~DoubleLinkedList(); //Destructor

	Node &operator ++();
	Node &operator ++(int);
	Node &operator --();	
	Node &operator --(int);
	Node &DoubleLinkedList::operator + (DoubleLinkedList& a);
	Node &DoubleLinkedList::operator [] (const int nIndex);

};
