#include "employee.h";

Employee::Employee(string theName, float thePayRate) {
	name = theName;
	payRate = thePayRate;
}

float Employee::getPayRate() {
	return payRate;
}

string Employee::getName() {
	return name;
}

float Employee::calculatePay(float hoursWorked) {
	return payRate*hoursWorked;
}