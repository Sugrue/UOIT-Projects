#include<iostream>;
#include<string>;

using namespace std;

struct foo {
	int k;
	int a[50];

};
int main() {
	int p[50];

	foo*myFoo = new foo();
	int*g = (int*)myFoo->k;
	int*d = (int*)myFoo->a;

	cout<<d<<endl;

//	for (int i = 0; i<50; i++)
	//	cout<<p+i<<endl;


	double myDouble = 5.5;
	int myInt = (int)myDouble;


	cout<<"myDouble:"<<myDouble<<"    myInt:"<<myInt<<endl;


	system("pause");
	return 0;
}