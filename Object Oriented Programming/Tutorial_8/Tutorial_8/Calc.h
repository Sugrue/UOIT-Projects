

class Calc {
public: 
	int multiply (int x , int y);
	int add(int x, int y);
	int divide (int x, int y);
};

int Calc::multiply(int x, int y)
{
	return x*y;
}

int Calc::add(int x, int y)
{
	return x+y;
}

int Calc::divide(int x, int y)
{
	if (y == 0)
		return 0;
	return x/y;
}