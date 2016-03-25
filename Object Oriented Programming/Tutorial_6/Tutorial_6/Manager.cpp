#include "manager.h"

Manager::Manager(string theName, float thePayRate, bool isSalaried)
	:Employee(theName, thePayRate) {
		salaried = isSalaried;
}

bool Manager::getSalaried() {
	return salaried;
}

float Manager::calculatePay(float hoursWorked) {
	if (salaried)
		return getPayRate();
	else
		return hoursWorked*getPayRate();

}