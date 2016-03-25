#include "OddInt.h";

void OddInt::setOddInt(int num) {
	if (num % 2 ==0) 
		num += 1;

	oddInt = num;

}