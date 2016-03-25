# include <iostream>
using namespace std;
template <class elemType>
struct nodeType
{
	elemType info;
	nodeType<elemType> *llink; 
	nodeType<elemType> *rlink;
};
template <class elemType>
class BinaryTreeType
{
public:
	bool isEmpty() 	{ return (root == NULL);}

	int height(nodeType<elemType> *p) {
		if (p == NULL)
			return 0;
		else
			return 1 + max(height(p->llink), height(p->rlink));
	}
	int nodeCount(nodeType<elemType> *p) {
		if (p == NULL)
			return 0;
		else
			return 1 + nodeCount(p->llink) + nodeCount(p->rlink);
	}
	int leavesCount(nodeType<elemType> *p) {
		if (p == NULL)
			return 0;
		else if ((p->llink == NULL) && (p->rlink == NULL))
			return 1;
		else
			return (leavesCount(p->llink) + leavesCount(p->rlink));
		return 0;
	}
	void preorder(nodeType<elemType> *p) {
		if (p != NULL)
		{
			cout << p->info << " ";
			preorder(p->llink);
			preorder(p->rlink);
		}
	}
	void inorder(nodeType<elemType> *p) {
		if (p != NULL)
		{
			inorder(p->llink);
			cout << p->info << " ";
			inorder(p->rlink);
		}
	}
	void postorder(nodeType<elemType> *p) {
		if (p != NULL)
		{
			postorder(p->llink);
			postorder(p->rlink);
			cout << p->info << " ";
		}
	}
	nodeType<elemType> *root;
};