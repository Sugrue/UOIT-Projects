#ifndef SLLIST_H
#define SLLIST_H

struct node
{
	char *name;
	int id;
	node *next;
};

class SLList
{
public:
	SLList();
	void insertFirst(char *name, int id);
	void insertLast(char *name, int id);
	bool isEmptyList();
	int length();
	node *front();
	void destroyList();
	bool searchName(const char *name);
	bool searchID(const int id);
	
	void print();

private:
	node *first;
	node *last;
	int count;
};

#endif