#include <iostream>;
#include <string>;
using namespace std;


class OddInt {
public: 
	void setOddInt(int num);
	friend istream &operator>>(istream &, OddInt &);

private: 
	int oddInt;
}