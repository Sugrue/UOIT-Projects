#include <string>;
using namespace std;


class Employee {
public:
	Employee(string theName, float thePayRate);

	float getPayRate();
	string getName();

	//calculates workers pay
	virtual float calculatePay(float hoursWorked);

private:
	float payRate;
	string name;

};