#include <stdexcept>;
using namespace std;


class myException : public out_of_range {
	: out_of_range("Index out of range");
}