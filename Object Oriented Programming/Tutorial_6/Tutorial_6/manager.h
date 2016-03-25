#include "employee.h"


class Manager: public Employee {
public:
	Manager(string theName, float thePayRate, bool isSalaried);

	bool getSalaried();
	virtual float calculatePay(float hoursWorked);

private:
	bool salaried;

};