#include "manager.h"
#include <iostream>


int main() 
{
	Employee * employee1 = new Employee("John", 12.0);
	Employee * employee2 = new Manager ("Jane", 25000.0, 1);

	Employee myEmployee("John", 12.0);
	Manager myManager("Jane", 25000.0, 1);


	cout<<"The guy's name is "<<employee1->getName()<<endl;
	cout<<"The manager's name is "<<employee2->getName()<<endl;

	cout<<"The employee's pay is "<<employee1->calculatePay(40.0)<<endl;
	cout<<"The manager's pay is "<<employee2->calculatePay(40.0)<<endl;

	system("pause");
	return 0;

}