#include <iostream>;

using namespace std;

void replace( int a[], int size, int index, int value) {

	try{
		if (index > size-1) 
			throw index;

		a[index] = value;
	}
	catch(int e){
		cout<<e<<" is too big"<<endl;
	}

	//if (index < size) 
		
}

int main() {

	const int SIZE = 5;

	int Array[SIZE];
	int Index;
	int Value;

	
	cout<<"Please enter some numbers:"<<endl;
	for (int i = 0; i< SIZE; i++) {
		cout<<i<<": ";
		cin>>Array[i];
		cout<<endl;
	}

	cout<<endl<<endl<<"Great. Lets swap a number"<<endl;
	cin>>Index;
	cout<<endl<<"Value: ";
	cin>>Value;

	replace(Array, SIZE, Index, Value);

	cout<<endl<<endl<<"NUMBERS:"<<endl;
	for (int i = 0; i<SIZE; i++) 
		cout<<Array[i]<<endl;

	system("Pause");
	return 0;
}