template <class A_Type> class BetterCalc
{
public:
	A_Type multiply(A_Type x, A_Type y);
	A_Type add(A_Type x, A_Type y);
	A_Type divide (A_Type x, A_Type y);
};

template <class A_Type> A_Type BetterCalc<A_Type>::multiply(A_Type x, A_Type y)
{
	return x*y;
}

template <class A_Type> A_Type BetterCalc<A_Type>::add(A_Type x, A_Type y)
{
	return x+y;
}

template <class A_Type> A_Type BetterCalc<A_Type>::divide(A_Type x, A_Type y)
{
	if(y==0)
		return 0;
	return x/y;
}