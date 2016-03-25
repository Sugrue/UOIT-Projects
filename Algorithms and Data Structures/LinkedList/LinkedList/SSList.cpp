#include <iostream>
#include <assert.h>
#include "SLList.h" 
using namespace std;
SLList::SLList()
{
	first = NULL;
	last = NULL;
	count = 0;
}

void SLList::print()
{
	cout << "List count: " << count <<endl;
	node *temp;
	temp = first;
	while(temp != NULL)
	{
		cout <<"Name = " <<temp->name <<endl;
		cout <<"ID = " <<temp->id <<endl;
		cout <<"======================" <<endl;
		temp = temp->next;
	}
}
void SLList::insertFirst(char *name, int id)
{
	node *newNode;
	newNode = new node;
	assert (newNode != NULL);
	newNode->name = name;
	newNode->id = id;
	newNode->next = first;
	first = newNode;
	if(last == NULL)
		last = newNode;
	count++;
}

void SLList::insertLast(char *name, int id)
{
	node *newNode;
	newNode = new node;
	assert (newNode != NULL);
	newNode->name = name;
	newNode->id = id;

	newNode->next = NULL;       
	if(first == NULL)	
	{
		first = newNode;
		last = newNode;
		count++;		
	}
	else			
	{
		last->next = newNode; 
		last = newNode;  
		count++;		
	}
}

bool SLList::searchName(const char *name)
{
    node *current; 
    bool found;

    current = first;  
                     
    found = false;   

    while(current != NULL && !found)		
		if(current->name == name)     
           found = true;
        else
           current = current->next; 
     
     return found;
}

bool SLList::searchID(const int id)
{
    node *current; 
    bool found;

    current = first;  
                     
    found = false;   

    while(current != NULL && !found)		
		if(current->id == id)     
           found = true;
        else
           current = current->next; 
     
     return found;
}

bool SLList::isEmptyList()
{
	return(first == NULL);
}

int SLList::length()
{
 	return count;
} 

node *SLList::front()
{   
    assert(first != NULL);
   	return first; 
}

void SLList::destroyList()
{
	node *temp; 	 
					
	while(first != NULL)   		 
	{
	   temp = first;       	 
	   first = first->next; 	
	   delete temp;         	
	}
	last = NULL;		
                   		
 	count = 0;
}