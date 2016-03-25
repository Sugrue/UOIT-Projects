# include "binaryTreeType.h"
# include <assert.h>
using namespace std;


template <class elemType>
class bSearchTreeType : public BinaryTreeType<elemType>
{
public:
	bSearchTreeType() { root = NULL;}

	bool search(const elemType& searchItem)
	{
		nodeType<elemType> *current;
		bool found = false;
		if (root == NULL)
			cerr << "Cannot search the empty tree." << endl;
		else
		{
			current = root;
			while (current != NULL && !found)
			{
				if (current->info == searchItem)
					found = true;
				else
				if (current->info > searchItem)
					current = current->llink;
				else
					current = current->rlink;
			}
		}
		return found;
	}
	void insert(const elemType& insertItem) {
		nodeType<elemType> *current;
		nodeType<elemType> *trailCurrent = NULL;
		nodeType<elemType> *newNode;

		newNode = new nodeType<elemType>;
		assert(newNode != NULL);
		newNode->info = insertItem;
		newNode->llink = NULL;
		newNode->rlink = NULL;

		if (root == NULL)
			root = newNode;
		else
		{
			current = root;
			while (current != NULL)
			{
				trailCurrent = current;
				if (current->info == insertItem)
				{
					//cerr << "The item is already in the tree  ";
					//cerr << "duplicates are not allowed." << endl;
					return;
				}
				else if (current->info > insertItem)
					current = current->llink;
				else
					current = current->rlink;
			}
			if (trailCurrent->info > insertItem)
				trailCurrent->llink = newNode;
			else
				trailCurrent->rlink = newNode;
		}
	}
	int display(nodeType<elemType> *p) {
		if (root == NULL) {
			cout << "TREE IS NOT INITIALIZED"<<endl;
			return 0;
		}
			
		 if (p->llink != NULL)
			display(p->llink);
		 if (p->rlink != NULL)
			display(p->rlink);
		 cout << p->info<<" ";
		return 0;
	}
	int singleParentCount(nodeType<elemType> *p) {
		int counter = 0;
		if (root == NULL) {
			cout << "TREE IS NOT INITIALIZED"<<endl;
			return 0;
		}

		if (p->llink != NULL && p->rlink != NULL) {
			counter += singleParentCount(p->llink);
			counter += singleParentCount(p->rlink);
			return counter;
		}
		if (p->llink != NULL)
			counter += singleParentCount(p->llink);
		if (p->rlink != NULL)
			counter += singleParentCount(p->rlink);
		if (p->rlink == NULL && p->llink == NULL)
			return 0;

		counter++;
		return counter;
	}
	int lessThanValueCount(nodeType<elemType> *p, int value) {
		if (root == NULL) {
			cout << "TREE IS NOT INITIALIZED"<<endl;
			return 0;
		}

		int counter = 0;

		if (p->llink != NULL)
			counter += lessThanValueCount(p->llink, value);
		if (p->rlink != NULL)
			counter += lessThanValueCount(p->rlink,  value);
		
		if (p->info < value)
			counter++;
		return counter;
	}
};