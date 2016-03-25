# include "bSearchTreeType.h"
# include <sys/timeb.h>

using namespace std;


int getMilliCount(){
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}
int getMilliSpan(int nTimeStart){
	int nSpan = getMilliCount() - nTimeStart;
	if (nSpan < 0)
		nSpan += 0x100000 * 1000;
	return nSpan;
}
int random(int max, int min) { return rand() % max + min; }

int main()
{
	//Cout statement for duplicate values has been commented out to prevent the output from interfering with the chart
	//See document for full description of the 3 functions
	//Main simply provides a quick driver for the tree, runtime analysis is done first, followed by a simple test of an un initialized list, followed by a quick test of all 3 functions.

	bSearchTreeType<int> *tree = new bSearchTreeType<int>;

	int time = 0;
	int value[14] = { 10, 20, 40, 80, 160, 320, 640, 1280, 2560, 5120, 10240, 20480, 40960, 81920 };
	int j = 0;

	cout << "Random numbers" << endl;

	cout << "Value  \t|\tTime" << endl
		<< "========+===========" << endl;

	for (j = 0; j < 14; j++) {
		time = getMilliCount();

		//random number in a sorted list
		for (int i = 0; i < value[j]; i++)
			tree->insert(random(32767, 0));

		cout << value[j] << "\t|\t" << getMilliSpan(time)<< endl;
		tree = new bSearchTreeType<int>;
	}
	
	cout <<endl<<endl<<endl<< "Sorted List of Numbers" << endl;

	cout << "Value  \t|\tTime" << endl
		<< "========+===========" << endl;

	for (j = 0; j < 14; j++) {
		time = getMilliCount();

		//random number in a sorted list
		for (int i = 0; i < value[j]; i++)
			tree->insert(i);

		cout << value[j] << "\t|\t" << getMilliSpan(time) << endl;
		tree = new bSearchTreeType<int>;
	}

	
	tree = new bSearchTreeType<int>;

	cout << "Testing Tree" << endl;
	cout << "tree->display result:";
	tree->display(tree->root);
	

	cout << endl << "Initilizing the tree" << endl;
	
	tree->insert(60);
	tree->insert(50);
	tree->insert(70);
	tree->insert(53);
	tree->insert(30);
	tree->insert(20);
	tree->insert(1);
	tree->insert(0);

	cout << "tree->display result:";

	tree->display(tree->root);


	cout << endl<<"tree->singleParentCount(tree->root):"<< tree->singleParentCount(tree->root);
	cout << endl << "tree->lessThenValueCount(tree->root,2):" << tree->lessThanValueCount(tree->root, 2) << endl;

	system("pause");
	return 0;
}